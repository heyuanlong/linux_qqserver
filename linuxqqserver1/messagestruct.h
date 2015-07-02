#ifndef MESSAGESTRUCT_H
#define MESSAGESTRUCT_H


#include "conf.h"

#include <queue>
#include <string.h>
#include <string>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>


//-----------------
//�ͻ��˷�������Ϣһ���������ָ�ʽ������ͻ��˷�������Ϣ���ǱȽϵ�һ������ע������
struct messagestruct
{
	int type;//��Ϣ����
	char qq1[11];//qq����
	char qq2[11];//qq����
	struct in_addr ip;//ip��ַ
	std::string mess;//qq��Ϣ

	void resume()
	{
		type = 0;
		strcpy(qq1, "");
		strcpy(qq2, "");
		ip.s_addr = 0;
		mess = "";
	}
};
struct sockerjson//������ջ������Ľṹ��
{
	//sockerjson(in_addr a, std::string b) :ip(a), jsonstr(b){}
	struct in_addr ip;
	std::string jsonstr;
};

/*struct jsonandcs//�߳�1ʹ��
{
	std::queue<sockerjson> *jm;
	//pthread_mutex_t& lpcs;
};
*/

//---------------------------------------------------
//���������ṹ�壬һ����ado�з��صĽṹ��

struct jsonout_ip//�߳�6����ip��ַ����jsonout
{
	struct in_addr ip;
	std::string jsonout;
};
struct friendtable//�����б�
{
	int groupid;
	std::string groupname;
	std::string you;//����qq����
	int online;

};


struct messageforreg//����ע��Ľṹ��
{
	std::string pa;
	std::string nickname;
	std::string realname;

	int age;
	int sex;

	void resume()
	{
		age = 0;
		sex = 0;
		pa = "";
		nickname = "";
		realname = "";
	}
};


struct messageqqinfo//qq������Ϣ
{
	std::string qq;
	std::string nickname;
	std::string realname;
	int age;
	int sex;

	void resume()
	{
		age = 0;
		sex = 0;
		qq = "";
		nickname = "";
		realname = "";
	}
};
struct messageqqfriend//qq�����б�
{
	std::string me;
	std::string you;
	int groudid;
	std::string groudname;

	void resume()
	{
		groudid = 0;
		me = "";
		you = "";
		groudname = "";
	}
};
struct qqmessagestruct//qq�����б�
{
	std::string sender;
	int classid;
	std::string mess;
	std::string time;

	void resume()
	{
		classid = 0;
		sender = "";
		time = "";
		mess = "";
	}
};


#endif
//���͸��ͻ��˵���ʾ��Ϣͳһ����Ϊ10