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

	std::string insert(std::string pa, std::string nick, std::string real, int age, int sex);//����û�
	void insert(std::string qq1, std::string qq2,int classid, std::string message, int status);//��Ӻ�������

	messagestruct insert(messagestruct);
	messageqqinfo findqq(std::string qq2);//
	int findqqpass(std::string qq, std::string pass);//qq�������Ƿ���ȷ
	void findfriend(char * qq, std::vector<friendtable>* vec);//�����б�
	int findfriend(char *qq1, char *qq2);//�Ƿ�Ϊ������
	void mymessage(char *qq, std::vector<qqmessagestruct>* vec);//�ҵĴ洢�����ݿ��qq��Ϣ

	int addfriend(char *qq1, char *qq2);//��Ӻ��ѹ�ϵ


 	MYSQL mysql;     
 	MYSQL_RES *res;
 	MYSQL_ROW row;
};







#endif