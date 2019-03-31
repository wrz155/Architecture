/*
 * work.h
 *
 *  Created on: 2014年6月17日
 *      Author: zhujy
 */

#ifndef WORK_H_
#define WORK_H_

#define CLIENTCOUNT 256
#define BODYBUF 1024

struct msg_t
{
	unsigned char head[4];
	char body[BODYBUF];
};

class work
{
public:
	work(int port);
	~work();
	void run();

private:
	int setnonblocking(int st); //将socket设置为非阻塞
	int socket_accept();
	int socket_recv(int st);
	void user_logout(int st);
	int listen_st;
	int socket_client[CLIENTCOUNT]; //申明socket_client数组，管理client的socket连接
};



#endif /* WORK_H_ */
