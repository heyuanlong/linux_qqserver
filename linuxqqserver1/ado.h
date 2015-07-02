#ifndef ADO_H
#define ADO_H

#include <stdio.h>
#include "mysql.h"
#include <string.h>

#include "messagestruct.h"

class ado
{
public:
	ado();
	~ado();

	std::string insert(std::string pa, std::string nick, std::string real, int age, int sex);//添加用户
	void insert(std::string qq1, std::string qq2,int classid, std::string message, int status);//添加好友请求

	messagestruct insert(messagestruct);
	messageqqinfo findqq(std::string qq2);//
	int findqqpass(std::string qq, std::string pass);//qq和密码是否正确
	void findfriend(char * qq, std::vector<friendtable>* vec);//好友列表
	int findfriend(char *qq1, char *qq2);//是否为好友了
	void mymessage(char *qq, std::vector<qqmessagestruct>* vec);//我的存储在数据库的qq消息

	int addfriend(char *qq1, char *qq2);//添加好友关系


 	MYSQL mysql;     
 	MYSQL_RES *res;
 	MYSQL_ROW row;
};







#endif