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
	static myjson js;//myjson用于处理json格式的消息


	//-------------客户端对服务器的请求--------------------//
	jsonout_ip reg(messagestruct &m);//注册qq
	jsonout_ip login(messagestruct &m, std::queue<jsonout_ip>*jp);//登录qq,会查看数据库，是否有消息
	void logout(messagestruct &m);//退出qq
	jsonout_ip findqqinfo(messagestruct &m);//查找qq信息
	

	//要放入数据库暂时存储的
	void qqctos(messagestruct &m);//处理qq消息
	jsonout_ip addfriendask(messagestruct &m);//请求添加qq好友
	jsonout_ip addfriendreply(messagestruct &m);//回复添加qq好友
	jsonout_ip qqmessage(messagestruct &m);//qq消息


	//-----------------------------------------------------//


	//-------------服务器对客户端的发送信息----------------//
	void returnreg();//注册qq成功与否
	void returnqqinfo();//返回qq个人信息
	void returnqqfriend(); //返回好友列表

	//要放入数据库暂时存储的
	//使用
	void askaddfriend();//请求添加为好友
	void qqstoc();//处理qq消息
	//-----------------------------------------------------//

	static void* loginqq(void* lp);//处理客户端登录qq的工作
	static int setonline(char*, struct in_addr);
	static int quitonline(char*);
	static struct in_addr getonline(const char*);
	static int judgeonline(const char*);


	static std::map<std::string, struct in_addr> online;
};


#endif
/*
信息类型
1 注册
2 登录
3 退出
4 查找单个qq信息
5 获取qq好友列表

6 处理qq消息
7 添加qq好友

*/
