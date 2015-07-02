#include "conf.h"
#include "myjson.h"


myjson::myjson()
{
}
myjson::~myjson()
{
}
messagestruct myjson::readmessagehead(sockerjson sj)
{

	m.resume();
	const char* str12 = sj.jsonstr.c_str();
	reader.run(str12, root);
	m.type = root["type"].getint();
	//���������
	strcpy(m.qq1, root["qq1"].getstring().c_str());
	strcpy(m.qq2, root["qq2"].getstring().c_str());
	
	JYJSON::Write writer;
	JYJSON::ValueObj temp;
	temp=root["message"].getobject();
	writer.run(temp,m.mess);	
	m.ip = sj.ip;

	root.clean();
	return m;
}

messageforreg myjson::readforreg(std::string str)
{
	mr.resume();

	const char* str12 = str.c_str();
	reader.run(str12, root);

	mr.age = root["age"].getint();
	mr.sex = root["sex"].getint();
	mr.pa = root["pass"].getstring().c_str();
	mr.nickname = root["nickname"].getstring().c_str();
	mr.realname = root["realname"].getstring().c_str();

	root.clean();
	return mr;
}
std::string myjson::readpass(std::string str12)
{
	reader.run(str12, root);
	std::string str = root["pass"].getstring().c_str();
	root.clean();
	return str;
}
std::string myjson::readqqmessage(std::string str12)
{
	reader.run(str12, root);
	std::string str = root["mess"].getstring().c_str();
	root.clean();
	return str;

}












////////-------------------------����json----------------------
//���͸��ͻ��˵���ʾ��Ϣͳһ����Ϊ10��11��10Ϊʧ�ܣ�11Ϊ�ɹ�
//����qq������Ϣ12
std::string myjson::jsonout(int i, std::string str)
{

	obj["type"] = i;
	obj["message"] = str;
	JYJSON::Write writer;
	std::string strWrite;
	writer.run(obj,strWrite);
	
	obj.clean();
	return strWrite;
}

std::string myjson::jsonout(int i, messageqqinfo inf)
{

	obj["type"] = i;
	obj["qq"] = inf.qq;
	obj["nickname"] = inf.nickname;
	obj["realname"] = inf.realname;
	obj["age"] = inf.age;
	obj["sex"] = inf.sex;

	JYJSON::Write writer;
	std::string strWrite;
	writer.run(obj,strWrite);
	

	obj.clean();
	return strWrite;
}
std::string myjson::jsonout(int i, std::vector<friendtable> *inf)
{
	obj["type"] = i;

	std::vector<friendtable>::iterator first = inf->begin();
	std::vector<friendtable>::iterator last = inf->end();
	int a = 0;
	while (first != last)
	{
		obj["message"][a]["groupid"] = first->groupid;
		obj["message"][a]["groupname"] = first->groupname;
		obj["message"][a]["you"] = first->you;
		obj["message"][a]["online"] = first->online;
		++first;
		++a;
	}
	JYJSON::Write writer;
	std::string strWrite;
	writer.run(obj,strWrite);
	

	obj.clean();
	return strWrite;
}

std::string myjson::jsonout(int i, messagestruct inf)
{

	obj["type"] = i;
	obj["qq"] = inf.qq1;
	obj["message"] = inf.mess.c_str();

	JYJSON::Write writer;
	std::string strWrite;
	writer.run(obj,strWrite);
	

	obj.clean();
	return strWrite;
}
std::string myjson::jsonout(int i, qqmessagestruct inf)//�洢�����ݿ��qq��Ϣ
{
	obj["type"] = i;
	obj["qq"] = inf.sender;
	obj["message"] = inf.mess.c_str();
	obj["time"] = inf.time.c_str();

	JYJSON::Write writer;
	std::string strWrite;
	writer.run(obj,strWrite);
	

	obj.clean();
	return strWrite;
}