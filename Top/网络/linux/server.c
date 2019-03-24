#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <sys/epoll.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <dirent.h>

#define BUFSIZE 262144  //256k

int socket_create(int port) //创建参数port指定端口号的server端socket
{
	int st = socket(AF_INET, SOCK_STREAM, 0); //创建TCP Socket
	int on = 1;
	if (setsockopt(st, SOL_SOCKET, SO_REUSEADDR, &on, sizeof(on)) == -1)
	{
		printf("setsockopt failed %s\n", strerror(errno));
		return 0;
	}
	struct sockaddr_in addr;
	memset(&addr, 0, sizeof(addr));
	addr.sin_family = AF_INET;
	addr.sin_port = htons(port);
	addr.sin_addr.s_addr = htonl(INADDR_ANY);
	if (bind(st, (struct sockaddr *) &addr, sizeof(addr)) == -1)
	{
		printf("bind port %d failed %s\n", port, strerror(errno));
		return 0;
	}
	if (listen(st, 300) == -1)
	{
		printf("listen failed %s\n", strerror(errno));
		return 0;
	}
	return st; //返回listen的socket描述符
}

int setnonblocking(int st) //将socket设置为非阻塞
{
	int opts = fcntl(st, F_GETFL);
	if (opts < 0)
	{
		printf("fcntl failed %s\n", strerror(errno));
		return 0;
	}
	opts = opts | O_NONBLOCK;
	if (fcntl(st, F_SETFL, opts) < 0)
	{
		printf("fcntl failed %s\n", strerror(errno));
		return 0;
	}
	return 1;
}

void getdir(const char *dirname, char *buf) //得到参数dirname指定目录下的文件名列表，将结果放入buf中
{
	DIR *dp;
	struct dirent *dirp;
	dp = opendir(dirname);//打开参数dirname指定的目录名
	if (dp == NULL)
	{
		printf("error is %s\n", strerror(errno));
		strcpy(buf, strerror(errno));//将错误信息放入buf
		return;
	}

	char tmp[200];

	while ((dirp = readdir(dp)) != NULL)//循环遍历目录下每一个文件名
	{
		memset(tmp, 0, sizeof(tmp));
		sprintf(tmp, "%s\n", dirp->d_name);
		strcat(buf, tmp);//将文件名做为字符串追加到buf尾,每个文件名以\n结尾
	}
	closedir(dp);
	return;

}

int socket_recv(int st)
{
	char recvbuf[200];
	memset(recvbuf, 0, sizeof(recvbuf));
	char *sendbuf = malloc(BUFSIZE);
	memset(sendbuf, 0, BUFSIZE);
	ssize_t rc = recv(st, recvbuf, sizeof(recvbuf), 0); //接收来自client socket发送来的消息

	printf("收到客户端的消息是%s\n", recvbuf);

	if (rc <= 0) //接收失败
	{
		if (rc < 0)
			printf("recv failed %s\n", strerror(errno));
	} else //接收成功
	{
		getdir(recvbuf, sendbuf);//得到指定目录下的文件名列表，将结果放入sendbuf中
		send(st, sendbuf, strlen(sendbuf), 0);//将得到的文件名列表下发给client端socket
	}
	free(sendbuf);
	return rc;
}

int socket_accept(int listen_st)
{
	struct sockaddr_in client_addr;
	socklen_t len = sizeof(client_addr);
	memset(&client_addr, 0, sizeof(client_addr));
	int client_st = accept(listen_st,  (struct sockaddr *)&client_addr, &len); //接收到来自client的socket连接

	if (client_st < 0)
		printf("accept failed %s\n", strerror(errno));
	else
		printf("accept by %s\n", inet_ntoa(client_addr.sin_addr));
	return client_st; //返回来自client端的socket描述符
}

void run(int port)
{
	int listen_st = socket_create(port); //创建参数port指定端口号的server端socket
	setnonblocking(listen_st); //把socket设置为非阻塞方式
	struct epoll_event ev, events[200]; //声明epoll_event结构体的变量,ev用于注册事件,数组用于回传要处理的事件
	int epfd = epoll_create(200); //生成用于处理accept的epoll专用的文件描述符

	ev.data.fd = listen_st; //设置与要处理的事件相关的文件描述符
	ev.events = EPOLLIN | EPOLLERR | EPOLLHUP; //设置要处理的事件类型

	int seq = 0;

	epoll_ctl(epfd, EPOLL_CTL_ADD, listen_st, &ev); //注册epoll事件

	printf("seq=%d\n", seq++);

	int st = 0;
	while (1)
	{
		int nfds = epoll_wait(epfd, events, 200, -1); //等待epoll事件的发生
		if (nfds == -1)
		{
			printf("epoll_wait failed %s\n", strerror(errno));
			break;
		}
		int i = 0;
		for (; i < nfds; i++)
		{
			if (events[i].data.fd < 0)
				continue;

			if (events[i].data.fd == listen_st) //监测到一个SOCKET用户连接到了绑定的SOCKET端口，建立新的连接。
			{
				st = socket_accept(listen_st);
				if (st >= 0)
				{
					setnonblocking(st); //将来自client端的socket描述符设置为非阻塞
					ev.data.fd = st;
					ev.events = EPOLLIN | EPOLLERR | EPOLLHUP; //设置要处理的事件类型
					epoll_ctl(epfd, EPOLL_CTL_ADD, st, &ev); //将来自client端的socket描述符加入epoll
					printf("seq=%d\n", seq++);
					continue;
				}
			}
			if (events[i].events & EPOLLIN) //socket收到数据
			{
				st = events[i].data.fd;
				if (socket_recv(st) <= 0)
				{
					close(st);
					events[i].data.fd = -1;
				}
			}
			if (events[i].events & EPOLLERR) //socket错误。
			{
				st = events[i].data.fd;
				close(st);
				events[i].data.fd = -1;
			}

			if (events[i].events & EPOLLHUP) //socket被挂断。
			{
				st = events[i].data.fd;
				close(st);
				events[i].data.fd = -1;
			}
		}
	}
	close(epfd);
}

int main(int arg, char *args[])
{
	if (arg < 2)//如果没有参数，main函数退出
	{
		printf("usage:server port\n");
		return EXIT_SUCCESS;
	}

	int iport = atoi(args[1]);//将第一个参数转化为端口号
	if (iport == 0)
	{
		printf("port %d is invalid\n", iport);
		return EXIT_SUCCESS;
	}
	run(iport);
	return EXIT_SUCCESS;
}

