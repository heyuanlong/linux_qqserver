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
//客户端发来的消息一定得是这种格式，本身客户端发来的消息就是比较单一，除了注册请求
struct messagestruct
{
	int type;//消息类型
	char qq1[11];//qq号码
	char qq2[11];//qq号码
	struct in_addr ip;//ip地址
	std::string mess;//qq消息

	void resume()
	{
		type = 0;
		strcpy(qq1, "");
		strcpy(qq2, "");
		ip.s_addr = 0;
		mess = "";
	}
};
struct sockerjson//放入接收缓冲区的结构体
{
	//sockerjson(in_addr a, std::string b) :ip(a), jsonstr(b){}
	struct in_addr ip;
	std::string jsonstr;
};

/*struct jsonandcs//线程1使用
{
	std::queue<sockerjson> *jm;
	//pthread_mutex_t& lpcs;
};
*/

//---------------------------------------------------
//服务端所需结构体，一般是ado中返回的结构体

struct jsonout_ip//线程6根据ip地址发送jsonout
{
	struct in_addr ip;
	std::string jsonout;
};
struct friendtable//好友列表
{
	int groupid;
	std::string groupname;
	std::string you;//好友qq号码
	int online;

};


struct messageforreg//用于注册的结构体
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


struct messageqqinfo//qq个人信息
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
struct messageqqfriend//qq好友列表
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
struct qqmessagestruct//qq好友列表
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
//发送给客户端的提示消息统一类型为10