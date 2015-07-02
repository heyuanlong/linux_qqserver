#ifndef COMMUNICATION_H
#define COMMUNICATION_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#include "messagestruct.h"


class communication
{
public:
	communication();
	~communication();
	int send(jsonout_ip);//发送

	static void* RecvProc(void* lpParameter);//接收
	static int m_socket;//init_socke函数初始化m_socket
	static int init_socke();

private:
	struct sockaddr_in addrTo;
	static struct sockaddr_in addrSock;
    static int const POST;
};

#endif

