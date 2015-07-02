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

//----ȫ�ֶ���-------
core mycore;

//һ���ô���center::Ŷ
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
�����߳�1,������Ϣ��������Ϣ����jsonmessagein--queue.
�����߳�2,ȡ��jsonmessagein�е���Ϣ-��������Ϊmessagestruct->���䵽struct1��struct2
�����߳�3������ע�ᣬ��¼���˳����鿴qq������Ϣ
�����߳�4������qq��Ϣ�ͺ������
�����߳�5������json��ʽ����Ϣ���ͻ���
*/
bool center::run()
{
	if (haverun != 1)
	{
	pthread_attr_t attr;
	pthread_attr_init(&attr);
	pthread_attr_setdetachstate(&attr,PTHREAD_CREATE_DETACHED);//�����߳�

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
void* center::takeoutjsin(void* lp)//�߳�2��stackjsonmessageinȡ����Ϣ����struct1��struct2
{
	myjson js;//myjson���ڴ���json��ʽ����Ϣ
	sockerjson jsonm;
	messagestruct m;
	int delay = 0;
	FL;
	while (true)
	{
		lock12();
		if (jsonmessagein.empty() == false)//�������ж��Ƿ�Ϊ��
		{FL;
			 jsonm= jsonmessagein.front();
			 jsonmessagein.pop();
		unlock12();

				 m = js.readmessagehead(jsonm);
				 //����m�����ݵ�strct1��struct2
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

				 //��������
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
void* center::dispose1(void* lp)//�߳�3����struct1->jsonmessageout
{
	int delay = 0;
	messagestruct m;
	jsonout_ip jsip;
	FL;
	while (true)
	{
		lock23();
		if (struct1.empty() == false)//�������ж��Ƿ�Ϊ��
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
void* center::dispose2(void* lp)//�߳�4����struct2
{
	int delay = 0;
	messagestruct m;
	jsonout_ip jsip;
	FL;
	while (true)
	{	
			lock24();
		if (struct2.empty() == false)//�������ж��Ƿ�Ϊ��
		{FL;					
			m = struct2.front();
			struct2.pop();
			unlock24();

			switch (m.type)
			{
			case 6:
				//qq��Ϣ
				jsip = mycore.qqmessage(m);
				break;
			case 7://7 �������qq����
				jsip = mycore.addfriendask(m);				
				break;
			case 8:///8 �ظ���Ӻ���
				jsip = mycore.addfriendreply(m);//a��b��a�ò����Ƿ��Ϊ�����ˡ�
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

void* center::sendjsonout(void* lp)//����jsonmessageout
{
	int delay = 0;
	jsonout_ip m;
	communication sm;
	FL;
	while (true)
	{
		lock36();	
		if (jsonmessageout.empty() == false)//�������ж��Ƿ�Ϊ��
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



