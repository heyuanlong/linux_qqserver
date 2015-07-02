#ifndef MYJSON_H
#define MYJSON_H

#include "jyjson/read.h"
#include "jyjson/write.h"
#include "messagestruct.h"
#include <string>
#include <string.h>
class myjson
{
public:
	myjson();
	~myjson();
	messagestruct readmessagehead(sockerjson);
	messageforreg readforreg(std::string);
	std::string readpass(std::string);
	std::string readqqmessage(std::string);
	std::string makejson();

	std::string jsonout(int i, std::string str); //提示
	std::string jsonout(int i, messageqqinfo inf);//qq个人信息
	std::string jsonout(int i, std::vector<friendtable> *inf);//好友列表
	std::string jsonout(int i, messagestruct inf);//qq消息
	std::string jsonout(int i, qqmessagestruct inf);//存储在数据库的qq消息

private:
	JYJSON::Read reader;// 解析json用Json::Reader   
	JYJSON::ValueObj root; // Json::Value是一种很重要的类型，可以代表任意类型。如int, string, object, array...  
	JYJSON::ValueObj obj;   // 构建对象  
	messagestruct m;
	messageforreg mr;
};

#endif
/*
定义一个超级结构体放入单个头文件中
先读取信息的类型，继而获取当前类型对应的其他类型
也许这里还要使用到vector

把所有类型的信息均放入一个超级结构体中，根据结构体内容make json
*/

