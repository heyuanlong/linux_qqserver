#include "conf.h"
#include "communication.h"
#include "center.h"
//#include "lock.h"

#include <stdio.h>
#include <errno.h>
#include <iostream>
#include <queue>

extern void lock12();
extern void unlock12();//调试
//extern pthread_mutex_t mutex[4];

int communication::m_socket = communication::init_socke();//静态函数初始化静态数据
struct sockaddr_in communication::addrSock;
int const communication::POST=6000;


communication::communication()
{
	addrTo.sin_family = AF_INET;
	addrTo.sin_port = htons(6001);//要求客户端绑定这个端口
}
communication::~communication()
{
	close(m_socket);
}

int communication::init_socke()
{	

	int mmsocket = socket(AF_INET, SOCK_DGRAM, 0);//创建UDP socket
	if (-1 == mmsocket)
	{
		perror("套接字创建失败！\n");
		exit(1);
	}

	bzero(&addrSock,sizeof(addrSock));
	addrSock.sin_family = AF_INET;//
	addrSock.sin_port = htons(POST);//6000端口
	addrSock.sin_addr.s_addr = htonl(INADDR_ANY);//任意ip的数据

	int retval = bind(mmsocket, (struct sockaddr*)&addrSock, sizeof(addrSock));
	if (-1 == retval)
	{
		perror("套接字绑定失败！\n");
		exit(1);
	}
	return mmsocket;
}



void* communication::RecvProc(void* lpParameter)//传来临界区对象和接收缓冲区
{
	std::queue<sockerjson> *mstack = (std::queue<sockerjson> *)lpParameter;

	struct sockaddr_in addrFrom;
	socklen_t len = sizeof(addrFrom);//调试
	char recvBuf[1000];
	std::string rebuf;
	int retval;

	while (1)
	{
            //万一发送的数据过多呢？ 客户端限制！！！
		retval = recvfrom(communication::m_socket, recvBuf, 1000, 0, (struct sockaddr*)&addrFrom, &len);//调试
		if (-1 == retval)
			break;

		struct in_addr ip = addrFrom.sin_addr;

		std::cout<<"这里表示接受到数据:"<<recvBuf<<std::endl;//这里表示接受到数据ok
		FL;
		lock12();
		FL;
		mstack->push( sockerjson{ip,std::string(recvBuf) }  );//调试 -std=c++11
		FL;
		unlock12();

	}
	return 0;
}


int communication::send(jsonout_ip jp)
{
	addrTo.sin_addr = jp.ip;
	int n;
	n=sendto(communication::m_socket, jp.jsonout.c_str(), jp.jsonout.size()+1, 0, (struct sockaddr*)&addrTo, sizeof(addrTo));
	if (-1 == n)
		std::cerr<<"communication::send error\n";

	MYLOG("communication::send " + jp.jsonout);
	return 1;
}


