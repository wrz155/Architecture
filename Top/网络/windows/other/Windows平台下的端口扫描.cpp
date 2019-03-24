/*
2017/10/5
	旧函数	server.sin_addr.s_addr = inet_addr(Ip); //指定被扫描的IP地址
	新函数	inet_pton(AF_INET, Ip, &server.sin_addr); //我们使用了新函数

使用新函数需要添加头文件
#include <Ws2tcpip.h>

*/


#include <stdio.h>
#include <WinSock2.h>
#include <Ws2tcpip.h>
#pragma comment(lib, "Ws2_32")


int scan(char *Ip, int StartPort, int EndPort)
{
	WSADATA wsa;
	WSAStartup(MAKEWORD(2, 2), &wsa);  //使用winsock函数之前，必须用WSAStartup函数来装入并初始化动态连接库

	struct sockaddr_in server;
	server.sin_family = AF_INET;  //指定地址格式，在winsock中只能使用AF_INET
	inet_pton(AF_INET, Ip, &server);   //指定被扫描的IP地址

	for (int CurrPort = StartPort; CurrPort <= EndPort; CurrPort++)
	{
		SOCKET s = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
		server.sin_port = htons(CurrPort); //指定被扫描IP地址的端口号
		int ret = connect(s, (struct sockaddr *)&server, sizeof(server)); //连接

		if (0 == ret) //判断连接是否成功
		{
			printf("%s:%d Success O(∩_∩)O\n", Ip, CurrPort);
			closesocket(s);
		}
		else {
			printf("%s:%d Failed\n", Ip, CurrPort);
		}
	}

	WSACleanup();  //释放动态连接库并释放被创建的套接字
	return 1;
}

int main()
{
	scan("127.0.0.1", 9999, 10001);

	getchar();
	return 0;
}
