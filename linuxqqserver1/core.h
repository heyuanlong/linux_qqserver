#ifndef QQSERVER_H
#define QQSERVER_H

#include "messagestruct.h"
#include "ado.h"
#include "myjson.h"

#include <map>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

class core
{
public:
	core();
	~core();
	static ado myado;
	static myjson js;//myjson���ڴ���json��ʽ����Ϣ


	//-------------�ͻ��˶Է�����������--------------------//
	jsonout_ip reg(messagestruct &m);//ע��qq
	jsonout_ip login(messagestruct &m, std::queue<jsonout_ip>*jp);//��¼qq,��鿴���ݿ⣬�Ƿ�����Ϣ
	void logout(messagestruct &m);//�˳�qq
	jsonout_ip findqqinfo(messagestruct &m);//����qq��Ϣ
	

	//Ҫ�������ݿ���ʱ�洢��
	void qqctos(messagestruct &m);//����qq��Ϣ
	jsonout_ip addfriendask(messagestruct &m);//�������qq����
	jsonout_ip addfriendreply(messagestruct &m);//�ظ����qq����
	jsonout_ip qqmessage(messagestruct &m);//qq��Ϣ


	//-----------------------------------------------------//


	//-------------�������Կͻ��˵ķ�����Ϣ----------------//
	void returnreg();//ע��qq�ɹ����
	void returnqqinfo();//����qq������Ϣ
	void returnqqfriend(); //���غ����б�

	//Ҫ�������ݿ���ʱ�洢��
	//ʹ��
	void askaddfriend();//�������Ϊ����
	void qqstoc();//����qq��Ϣ
	//-----------------------------------------------------//

	static void* loginqq(void* lp);//����ͻ��˵�¼qq�Ĺ���
	static int setonline(char*, struct in_addr);
	static int quitonline(char*);
	static struct in_addr getonline(const char*);
	static int judgeonline(const char*);


	static std::map<std::string, struct in_addr> online;
};


#endif
/*
��Ϣ����
1 ע��
2 ��¼
3 �˳�
4 ���ҵ���qq��Ϣ
5 ��ȡqq�����б�

6 ����qq��Ϣ
7 ���qq����

*/
