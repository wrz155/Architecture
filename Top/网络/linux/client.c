#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define BUFSIZE 262144  //256k

int SocketConnect(const char *hostname, int port) //client端socket连接到hostname指定的IP地址和port端口号
{
	int st = socket(AF_INET, SOCK_STREAM, 0); //建立一个TCP socket描述符
	struct sockaddr_in addr;
	memset(&addr, 0, sizeof(addr));
	addr.sin_family = AF_INET;
	addr.sin_port = htons(port);
	addr.sin_addr.s_addr = inet_addr(hostname);
	if (connect(st, (struct sockaddr *) &addr, sizeof(addr)) == -1) //连接到指定IP
	{
		printf("connect to %s:%d failed %s\n", hostname, port, strerror(errno));
		return 0; //连接失败，返回0
	} else
	{
		printf("connect to %s:%d success\n", hostname, port);
		return st; //连接成功后返回socket描述符
	}
}

ssize_t SocketSend(int st, const char *s) //向server端socket发送数据，并接收来自server端的返回数据
{
	ssize_t rc = send(st, s, strlen(s), 0);
	if (rc <= 0)
	{
		printf("send failed, %s\n", strerror(errno));
		return rc;
	}

	char *buf = malloc(BUFSIZE);
	memset(buf, 0, BUFSIZE);
	rc = recv(st, buf, BUFSIZE, 0);
	if (rc <= 0) //如果recv失败，代表TCP连接中断，循环break
	{
		printf("recv failed, %s\n", strerror(errno));
	}else
	{
		printf("%s\n", buf);//如果接收到来自server端的数据，将数据打印到屏幕
	}
	free(buf);
	return rc;
}

int main(int arg, char *args[])
{
	if (arg < 3) //如果参数小于2个，main函数退出
	{
		return -1;
	}

	int iport = atoi(args[2]); //将第二个参数转化为整数
	if (iport == 0)
	{
		return -1;
	}
	
	int st = SocketConnect(args[1], iport); //第一个参数为IP地址，连接到第一个参数指定的IP地址
	if (st == 0) //连接失败，main函数退出
		return -1;

	char buf[200];

	while (1)
	{
		memset(buf, 0, sizeof(buf));
		read(STDIN_FILENO, buf, sizeof(buf));

		if (strncmp(buf, "exit", 4) == 0)
			break; //如果用户输入字符串exit，程序退出

		buf[strlen(buf) - 1] = 0;//将最后一个字符\n替换为0
		if (strlen(buf) == 0)
			continue;//如果为空字符串，循环continue

		if (SocketSend(st, buf) <=0)//将用户从键盘输入的数据发送到server端
			break;//如果socket_send调用失败，循环退出

	}

	close(st);
	return -1;
}

