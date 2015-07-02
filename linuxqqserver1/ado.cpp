#include "conf.h"
#include "ado.h"

#include "stdlib.h"
#include "string.h"
#include "time.h"
#include "stdio.h"
#include "string.h"
#include <exception>
#include <iostream>
//mysql_real_query 成功返回0.

ado::ado()
{
	mysql_init(&mysql);
 	if(!mysql_real_connect(&mysql,"localhost","forqq","222","qqserver",0,NULL,0))
 	{//若连接数据库失败
     	printf( "Failed to connect to MySQL！\n");
	}
 	else 	
		printf("Connected mysql successfully!\n"); 
}

ado::~ado()
{	
	mysql_close(&mysql);  
}

std::string ado::insert(std::string pa, std::string nick, std::string real, int age, int sex)
{
	srand(static_cast<unsigned int>(time(NULL)));
	char qq[11] = { 0 };

//while(1){std::cout<<rand()<<std::endl;}

	for (int n = 0; n <= 9; n++)//要10个字符
	{
		qq[n]='0' + (rand() % 10 );
	}

std::cout<<qq<<std::endl;

	MYLOG("ado::insert1 user");

	try{
			char inuser[100];
			sprintf(inuser, "insert into user values('%s','%s')", qq,pa.c_str());
std::cout<<inuser<<std::endl;
			 if(mysql_real_query(&mysql,inuser,(unsigned int)strlen(inuser)))
			{
			   std::cout<<"insert user data failed!\n"<<std::endl;
			   return "";	
			}

			char inusermessage[150];
			sprintf(inusermessage, "insert into usermessage values('%s','%s','%s',%d,%d)", qq,nick.c_str(),real.c_str(),age,sex);
std::cout<<inusermessage<<std::endl;			
			if(mysql_real_query(&mysql,inusermessage,(unsigned int) strlen(inusermessage)))
			{
			   std::cout<<"insert usermessage data failed!\n"<<std::endl;
			   return "";	
			}

		}catch (std::exception &e)
		{			
			return "";
		}

		MYLOG("ado::insert success");
		return qq;	
}
void ado::insert(std::string qq1, std::string qq2, int classid, std::string message, int status)//添加好友请求
{
	MYLOG("ado::insert1 user");

	try{
			char inmessagetable[200];
			sprintf(inmessagetable, "insert into messagetable(sender,receiver,classid,message,status) values('%s','%s',%d,'%s',%d)", qq1.c_str(),qq2.c_str(),classid,message.c_str(),status);
			 if(mysql_real_query(&mysql,inmessagetable,(unsigned int) strlen(inmessagetable)))
			{
			   printf("insert messagetable data failed!\n"); 
			  
			}

	}catch (std::exception &e)
		{		
			std::cout<<"insert error";
			exit(1);
		}

	MYLOG("ado::insert success");
}

messageqqinfo ado::findqq(std::string qq2)
{
	MYSQL_RES *res;
	MYSQL_ROW row;

	messageqqinfo m;
	m.qq = "error";
	int t;
	try{
    char str_findqq[200];
    sprintf(str_findqq, "select * from usermessage where qq='%s'", qq2.c_str());

    t = mysql_real_query(&mysql,str_findqq,(unsigned int) strlen(str_findqq));
 	if (t)
 	{
  	  printf("Error making str_findqq query: %s\n",mysql_error(&mysql));
 	}
	
	char str[5][11];
 	res = mysql_store_result(&mysql);

 	while(row = mysql_fetch_row(res))//其实就一行
		for(t=0;t<mysql_num_fields(res);t++)
			strcpy(str[t],row[t]);


		m.qq = str[0];
		m.nickname = str[1];
		m.realname = str[2];
		m.age = atoi(str[3]);
		m.sex = atoi(str[4]);
	}catch (std::exception &e)
	{		
		return m;
	}
	MYLOG("ado::findqq success");
	return m;

}
int ado::findqqpass(std::string qq, std::string pass)
{
	MYSQL_RES *res;
	my_ulonglong nums;
	
   int t;
	try{
    char str_findqqpass[200];
    sprintf(str_findqqpass, "select * from user where qq='%s' and pass='%s'", qq.c_str(),pass.c_str());

    t = mysql_real_query(&mysql,str_findqqpass,(unsigned int) strlen(str_findqqpass));
	if (t)
	{
		printf("Error making str_findqqpass query: %s\n",
			mysql_error(&mysql));
	}
	
	res = mysql_store_result(&mysql); 
	nums = mysql_num_rows(res);

	if (nums > 0)
		return 1;
	else 
		return 0;

	}catch (std::exception &e)
	{		
		return 0;
	}

}
void ado::findfriend(char * qq, std::vector<friendtable>* vec)
{	
	MYSQL_RES *res;
	MYSQL_ROW row;

	int t;

	try{
    char str_findfriend[200];
    sprintf(str_findfriend, "select * from friend where me='%s'", qq);

    t = mysql_real_query(&mysql,str_findfriend,(unsigned int) strlen(str_findfriend));
	if (t)
	{
		printf("Error making str_findfriend query: %s\n",
			mysql_error(&mysql));
	}

	char str[4][11];
	friendtable m;
	res = mysql_store_result(&mysql); 

	 	while(row = mysql_fetch_row(res))
	 	{
			for(t=0;t<mysql_num_fields(res);t++)
			{
				strcpy(str[t],row[t]);
			}
			m.groupid=atoi(str[1]);
			m.groupname=str[2];
			m.you=str[3];

			vec->push_back(m);
	 }

	}catch (std::exception &e)
	{		
		exit(1);
	}

	MYLOG("ado::findqqfriendliebiao success");
}

/*
{  "type": 1,  "qq1": "012345689", "qq2": "11256789", "ip": "11456789", "message": {"pa": "mima",  "nick": "nick", "age": 10, "sex": 1 }}

*/


int ado::findfriend(char *qq1, char *qq2)
{

	MYSQL_RES *res;
	my_ulonglong nums;
	
	int t;
	try{
	    char str_findfriend[200];
	    sprintf(str_findfriend, "select * from friend where me='%s' and you='%s'", qq1,qq2);

	    t = mysql_real_query(&mysql,str_findfriend,(unsigned int) strlen(str_findfriend));
		if (t)
		{
			printf("Error making str_findfriend query: %s\n",
				mysql_error(&mysql));
		}
		
		res = mysql_store_result(&mysql); 
		nums = mysql_num_rows(res);
		if (nums > 0)
			return 1;
		else 
			return 0;

	}catch (std::exception &e)
	{		
		return 0;
	}

}
int ado::addfriend(char *qq1, char *qq2)//添加好友关系
{

	MYLOG("ado::addfriend user");

	try{
			char infriend[200];
			sprintf(infriend, "insert into friend values('%s','%d,'%s','%s')", qq1,0,"default",qq2);
			 if(mysql_real_query(&mysql,infriend,(unsigned int) strlen(infriend)))
			{
			   printf("insert friend data failed!\n"); 
			   return 0;	
			}

			sprintf(infriend, "insert into friend values('%s','%d,'%s','%s')", qq2,0,"default",qq1);
			 if(mysql_real_query(&mysql,infriend,(unsigned int) strlen(infriend)))
			{
			   printf("insert friend data failed!\n"); 
			   return 0;	
			}
		
	}catch (std::exception &e)
		{			
			return 0;
		}

	MYLOG("ado::addfriend success");
	return 1;
}

void ado::mymessage(char *qq, std::vector<qqmessagestruct>* vec)//我的存储在数据库的qq消息
{
	MYSQL_RES *res;
	MYSQL_ROW row;
	
int t;
try{
    char str_mymessage[200];
    sprintf(str_mymessage, "select * from messagetable where receiver='%s' and status=0", qq);

    t = mysql_real_query(&mysql,str_mymessage,(unsigned int) strlen(str_mymessage));
	if (t)
	{
		printf("Error making str_mymessage query: %s\n",
			mysql_error(&mysql));
	}

	char str[2][11];
	std::string messa;
	std::string metime;
	qqmessagestruct m;
	res = mysql_store_result(&mysql); 
	 	while(row = mysql_fetch_row(res))
	 	{
			for(t=0;t<mysql_num_fields(res);t++)
			{
				if(0 == t)
				strcpy(str[0],row[t]);
				else if(3 ==t)
				strcpy(str[1],row[t]);
				else if(4 ==t){
				messa=row[t];
				}
				else if(5 ==t){
				metime=row[t];
				break;
				}

			}

			m.sender = str[0];
			m.classid =atoi(str[1]);
			m.mess = messa;
			m.time = metime;

			vec->push_back(m);
	 }

	char str_updatemymessage[200];
	sprintf(str_updatemymessage, "update messagetable set status = 1 where status = 0 and receiver='%s'", qq);

	t = mysql_real_query(&mysql,str_updatemymessage,(unsigned int) strlen(str_updatemymessage));
	if (t)
	{
		printf("Error making str_updatemymessage query: %s\n",
			mysql_error(&mysql));
	}

	}catch (std::exception &e)
	{		
		exit(1);
	}

	MYLOG("ado::mymessage success");
}

