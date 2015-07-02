#include <stdio.h>
#include <stdlib.h>
#include <stdlib.h>
#include <pthread.h>

#include "center.h"
#include "conf.h"
#include "communication.h"
#include "myjson.h"
#include "messagestruct.h"
#include "core.h"
#include "lock.h"


//-----------
#define DELAY 2000
#define DELAYTIME 1

//----全局对象-------
core mycore;

//一定得带上center::哦
std::queue<sockerjson> center::jsonmessagein;
std::queue<messagestruct> center::struct1;
std::queue<messagestruct> center::struct2;
std::queue<jsonout_ip> center::jsonmessageout;
//------------------


center::center()
{
	haverun = 0;
}
center::~center()
{
}

/*
开启线程1,接收消息，并把消息放入jsonmessagein--queue.
开启线程2,取出jsonmessagein中的消息-》把它变为messagestruct->分配到struct1和struct2
开启线程3，处理注册，登录，退出，查看qq好友信息
开启线程4，处理qq消息和好友添加
开启线程5，发送json格式的消息到客户端
*/
bool center::run()
{
	if (haverun != 1)
	{
	pthread_attr_t attr;
	pthread_attr_init(&attr);
	pthread_attr_setdetachstate(&attr,PTHREAD_CREATE_DETACHED);//分离线程

	int t1 = pthread_create(&tid1, &attr, communication::RecvProc, (void*)&center::jsonmessagein);
	int t2 = pthread_create(&tid2, &attr, takeoutjsin, NULL);
	int t3 = pthread_create(&tid3, &attr, dispose1, NULL);
	int t4 = pthread_create(&tid4, &attr, dispose2, NULL);
	int t5 = pthread_create(&tid5, &attr, sendjsonout, NULL);

	pthread_attr_destroy(&attr);

	if (t1 != 0 || t2 != 0 || t3 != 0 || t4 != 0 || t5 != 0)
	{
		std::cerr<<"pthread_create error";
		exit(1);
	}

	haverun = 1;
	std::cout<<"run hThread";
	}
	else std::cout<<"haved run hThread";

	return true;
}
void* center::takeoutjsin(void* lp)//线程2从stackjsonmessagein取出消息放入struct1或struct2
{
	myjson js;//myjson用于处理json格式的消息
	sockerjson jsonm;
	messagestruct m;
	int delay = 0;
	FL;
	while (true)
	{
		lock12();
		if (jsonmessagein.empty() == false)//必须先判断是否为空
		{FL;
			 jsonm= jsonmessagein.front();
			 jsonmessagein.pop();
		unlock12();

				 m = js.readmessagehead(jsonm);
				 //分离m的数据到strct1和struct2
				 switch (m.type)
				 {
				 case 1:
				 case 2:
				 case 3:
				 case 4:
				 case 5:					
					 lock23();
					 struct1.push(m);
					 unlock23();		
					 break;
				 case 6:
				 case 7:
				 case 8:					
					 lock24();
					 struct2.push(m);
					 unlock24();
					 break;  
				 default:
					 break;
				 }

				 //重置数据
			//	 jsonm = "";
				 m.resume();
		}
		else{
		unlock12();
			++delay;
			if (delay == DELAY)
			{
				delay = 0; sleep(DELAYTIME);
			}
		}
	}
	FL;
	return 0;
}
void* center::dispose1(void* lp)//线程3处理struct1->jsonmessageout
{
	int delay = 0;
	messagestruct m;
	jsonout_ip jsip;
	FL;
	while (true)
	{
		lock23();
		if (struct1.empty() == false)//必须先判断是否为空
		{FL;					
			m = struct1.front();
			struct1.pop();
			unlock23();

			switch (m.type)
			{
			case 1:
				jsip = mycore.reg(m);
				break;
			case 2:
				jsip = mycore.login(m, &jsonmessageout);
				break;
			case 3:
				 mycore.logout(m);
				break;
			case 4:
				jsip = mycore.findqqinfo(m);
				break;
			case 5:
				//jsonout = mycore.getfriend(m);
				break;
			default:
				break;
			}
			MYLOG(" center::dispose1" + jsip.jsonout);
	
			lock36();		
			jsonmessageout.push(jsip);
			unlock36();
			
			m.resume();
		}
		else{
			unlock23();
			++delay;
			if (delay == DELAY)
			{
				delay = 0; sleep(DELAYTIME);
			}
		}
	}
	FL;
	return 0;
}
void* center::dispose2(void* lp)//线程4处理struct2
{
	int delay = 0;
	messagestruct m;
	jsonout_ip jsip;
	FL;
	while (true)
	{	
			lock24();
		if (struct2.empty() == false)//必须先判断是否为空
		{FL;					
			m = struct2.front();
			struct2.pop();
			unlock24();

			switch (m.type)
			{
			case 6:
				//qq消息
				jsip = mycore.qqmessage(m);
				break;
			case 7://7 请求添加qq好友
				jsip = mycore.addfriendask(m);				
				break;
			case 8:///8 回复添加好友
				jsip = mycore.addfriendreply(m);//a加b，a得不到是否加为好友了。
				break;
			default:
				break;
			}
			MYLOG(" center::dispose2" + jsip.jsonout);

			if (jsip.jsonout  != "")
			{
				lock36();	
				jsonmessageout.push(jsip);
				unlock36();					
			}		
			m.resume();
		}
		else{
			unlock24();
			++delay;
			if (delay == DELAY)
			{
				delay = 0; sleep(DELAYTIME);
			}
		}
	}
	FL;
	return 0;
}

void* center::sendjsonout(void* lp)//发送jsonmessageout
{
	int delay = 0;
	jsonout_ip m;
	communication sm;
	FL;
	while (true)
	{
		lock36();	
		if (jsonmessageout.empty() == false)//必须先判断是否为空
		{FL;					
			m = jsonmessageout.front();
			jsonmessageout.pop();
		unlock36();	

			sm.send(m);
		}
		else{
			unlock36();
			++delay;
			if (delay == DELAY)
			{
				delay = 0; sleep(DELAYTIME);
			}
		}

	}
	FL;
	return 0;
}



