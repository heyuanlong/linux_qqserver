#include "conf.h"
#include "communication.h"
#include "center.h"
//#include "lock.h"

#include <stdio.h>
#include <errno.h>
#include <iostream>
#include <queue>

extern void lock12();
extern void unlock12();//����
//extern pthread_mutex_t mutex[4];

int communication::m_socket = communication::init_socke();//��̬������ʼ����̬����
struct sockaddr_in communication::addrSock;
int const communication::POST=6000;


communication::communication()
{
	addrTo.sin_family = AF_INET;
	addrTo.sin_port = htons(6001);//Ҫ��ͻ��˰�����˿�
}
communication::~communication()
{
	close(m_socket);
}

int communication::init_socke()
{	

	int mmsocket = socket(AF_INET, SOCK_DGRAM, 0);//����UDP socket
	if (-1 == mmsocket)
	{
		perror("�׽��ִ���ʧ�ܣ�\n");
		exit(1);
	}

	bzero(&addrSock,sizeof(addrSock));
	addrSock.sin_family = AF_INET;//
	addrSock.sin_port = htons(POST);//6000�˿�
	addrSock.sin_addr.s_addr = htonl(INADDR_ANY);//����ip������

	int retval = bind(mmsocket, (struct sockaddr*)&addrSock, sizeof(addrSock));
	if (-1 == retval)
	{
		perror("�׽��ְ�ʧ�ܣ�\n");
		exit(1);
	}
	return mmsocket;
}



void* communication::RecvProc(void* lpParameter)//�����ٽ�������ͽ��ջ�����
{
	std::queue<sockerjson> *mstack = (std::queue<sockerjson> *)lpParameter;

	struct sockaddr_in addrFrom;
	socklen_t len = sizeof(addrFrom);//����
	char recvBuf[1000];
	std::string rebuf;
	int retval;

	while (1)
	{
            //��һ���͵����ݹ����أ� �ͻ������ƣ�����
		retval = recvfrom(communication::m_socket, recvBuf, 1000, 0, (struct sockaddr*)&addrFrom, &len);//����
		if (-1 == retval)
			break;

		struct in_addr ip = addrFrom.sin_addr;

		std::cout<<"�����ʾ���ܵ�����:"<<recvBuf<<std::endl;//�����ʾ���ܵ�����ok
		FL;
		lock12();
		FL;
		mstack->push( sockerjson{ip,std::string(recvBuf) }  );//���� -std=c++11
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


