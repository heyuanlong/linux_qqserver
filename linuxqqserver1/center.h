#ifndef CENTER_H
#define CENTER_H

#include "messagestruct.h"


class center
{
private:
	int haverun;
	pthread_t tid1,tid2,tid3,tid4,tid5;
public:
	center();
	~center();

	bool run();

	//如果是本类调用本类中的函数作为线程函数，则应该为static
	static void* takeoutjsin(void* lp);//线程2从stackjsonmessagein取出消息放入struct1或struct2
	static void* dispose1(void* lp);//线程3处理struct1->jsonmessageout
	static void* dispose2(void* lp);//线程4处理struct2

	static void* sendjsonout(void* lp);//线程6发送jsonmessageout


	static std::queue<sockerjson> jsonmessagein;//线程1获取的数据
	static std::queue<messagestruct> struct1;//线程2的结果
	static std::queue<messagestruct> struct2;//线程2的结果，struct2，这里的数据是可暂存数据如消息，添加好友

	//线程4处理struct2，是否直接发送或暂存
	static std::queue<jsonout_ip> jsonmessageout;//线程5把struct1变为json格式
	//线程6发送jsonmessageout

};

#endif

/*
信息类型
0 客户端主动请求刷新
1 注册
2 登录
3 退出
4 查找单个qq信息
5 获取qq好友列表

6 处理qq消息
7 请求添加qq好友
8 回复添加好友

//--------------------
110 给客户的失败提示信息
111注册成功
112查找qq个人信息
113qq好友列表
114添加好友请求
115 qq消息

200 让客户端去请求刷新
//--------------------

存入数据库的消息
classid 1 添加好友
classid 2 qq消息
状态 0为发送 1发送ok
*/

//char recvBuf[1001]; 接收的数据被限定了哦

/*
开启线程1,接收消息，并把消息放入jsonmessagein--queue.
开启线程2,取出jsonmessagein中的消息-》把它变为messagestruct->分配到struct1和struct2
开启线程3，处理注册，登录，退出，查看qq好友信息
开启线程4，处理qq消息和好友添加
开启线程5，发送json格式的消息到客户端
*/