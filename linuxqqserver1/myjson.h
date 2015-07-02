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

	std::string jsonout(int i, std::string str); //��ʾ
	std::string jsonout(int i, messageqqinfo inf);//qq������Ϣ
	std::string jsonout(int i, std::vector<friendtable> *inf);//�����б�
	std::string jsonout(int i, messagestruct inf);//qq��Ϣ
	std::string jsonout(int i, qqmessagestruct inf);//�洢�����ݿ��qq��Ϣ

private:
	JYJSON::Read reader;// ����json��Json::Reader   
	JYJSON::ValueObj root; // Json::Value��һ�ֺ���Ҫ�����ͣ����Դ����������͡���int, string, object, array...  
	JYJSON::ValueObj obj;   // ��������  
	messagestruct m;
	messageforreg mr;
};

#endif
/*
����һ�������ṹ����뵥��ͷ�ļ���
�ȶ�ȡ��Ϣ�����ͣ��̶���ȡ��ǰ���Ͷ�Ӧ����������
Ҳ�����ﻹҪʹ�õ�vector

���������͵���Ϣ������һ�������ṹ���У����ݽṹ������make json
*/

