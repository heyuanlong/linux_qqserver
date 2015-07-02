#include "conf.h"
#include "core.h"
#include "myjson.h"
//#include "lock.h"


#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>



extern void lock36();
extern void unlock36();//调试


std::map<std::string,struct in_addr> core::online;
ado core::myado;
myjson core::js;

core::core()
{
}


core::~core()
{
}
jsonout_ip core::login(messagestruct &m, std::queue<jsonout_ip>*jp)//登录qq,查看数据库，是否有消息,创建新线程
{


	//在内存中设置此qq号码的登录状态（包含ip）
	//好友列表
	//好友昵称
	//好友在线状态
	//组合这些信息
FL;

	using std::string;
	std::string jsonout;
	std::vector<friendtable> myfriend;
	std::vector<qqmessagestruct> mymess;

	char qq[11] = { 0 };
	strcpy(qq, m.qq1);
	struct	in_addr ip = m.ip;

	try{

		string pass = js.readpass(m.mess);
		if (myado.findqqpass(qq,pass) == 0)
		{
			jsonout = js.jsonout(110, "账户或密码错误");
			return jsonout_ip{ m.ip, jsonout };
		}
		setonline(qq, ip);
		//getfriend(qq, &myfriend);//获取qq好友列表
		myado.findfriend(qq, &myfriend);//获取qq好友列表
		

		std::vector<friendtable>::iterator first = myfriend.begin();
		std::vector<friendtable>::iterator last = myfriend.end();
		while (first != last)
		{
			first->online = judgeonline(first->you.c_str());
			++first;
		}

	}
	catch (std::exception e){
		jsonout = js.jsonout(110, "获取qq好友信息失败");
	}

	jsonout = js.jsonout(113, &myfriend);

	MYLOG("core::login" + jsonout);

	lock36();
	jp->push(jsonout_ip{ m.ip, jsonout });
	unlock36();


	try{
	myado.mymessage(qq, &mymess);
	}
	catch (std::exception e){
		jsonout = js.jsonout(110, "获取qq消息失败");
	}


	std::vector<qqmessagestruct>::iterator first = mymess.begin();
	std::vector<qqmessagestruct>::iterator last = mymess.end();
	while (first != last)
	{
		if (first->classid == 1)
		{
			jsonout = js.jsonout(114, *first);
		}		
		else if (first->classid == 2)
		{
			jsonout = js.jsonout(115, *first);
		}
		lock36();
		jp->push(jsonout_ip{ m.ip, jsonout });
		unlock36();

		++first;
		MYLOG("core::login " + jsonout);
	}

	MYLOG("core::login success");
FL;
	return jsonout_ip{ m.ip, "" };
}



jsonout_ip core::reg(messagestruct &m)//注册qq
{
	//先随机生成一个qq号码，判断有无
	//password nianname，age， sex
FL;
	messageforreg mr = js.readforreg(m.mess);
	std::string reg = myado.insert(mr.pa,mr.nickname,mr.realname,mr.age,mr.sex);
	//成功返回qq号码

	std::string jsonout;
	if (reg == "") 
		jsonout=js.jsonout(110, "注册失败");
	else 
		jsonout=js.jsonout(111, "注册成功，qq号码为："+reg);
	
	MYLOG("core::reg" + jsonout);

FL;
	return jsonout_ip{ m.ip, jsonout };
	
}

void core::logout(messagestruct &m)//退出qq
{
	//内存数据库中设置（包含ip）
	quitonline(m.qq1);

}
jsonout_ip core::findqqinfo(messagestruct &m)//查找qq个人信息
{
FL;
	messageqqinfo inf = myado.findqq(m.qq2);
	//构造json
	//发到jsonout
	std::string jsonout;
	if (inf.qq == "error")
		jsonout = js.jsonout(110, "查找qq个人信息失败");
	else
		jsonout = js.jsonout(112, inf);


	MYLOG("core::findqqinfo" + jsonout);
FL;
	 return jsonout_ip{ m.ip,jsonout };


}



//////----------设置qq在线状态和获取qq在线ip----------------////
int core::setonline(char* qq, struct in_addr ip)
{
FL;
	//char q[11] = { 0 };
	//strcpy(q, qq);
	std::map<std::string, struct in_addr>::value_type vt(qq, ip);
	std::pair<std::map<std::string, struct in_addr>::iterator, bool> re = online.insert(vt);

	if (!re.second)
	{
		online.erase(qq);
		online.insert(vt);
	}
FL;
	return 1;
}
int core::quitonline(char* qq)
{
	online.erase(qq);
	return 1;
}
struct in_addr core::getonline(const char* qq)
{
FL;
	//char q[11] = { 0 };
	//strcpy(q, qq);
	std::map<std::string, struct in_addr>::iterator f = online.find(qq);
	if (f == online.end() )
	{
		struct in_addr i;
		i.s_addr = 0;
		return i;
	}
FL;
	return f->second;
}
int core::judgeonline(const char* qq)
{
FL;
//char q[11] = { 0 };
	//strcpy(q, qq);
	std::map<std::string,struct in_addr>::iterator f = online.find(qq);
	if (f == online.end())
	{
		return 0;
	}
FL;
	return 1;
}
////////////////--------------------------------------------////////

jsonout_ip core::addfriendask(messagestruct &m)//添加qq好友
{
FL;	
	//{  "type": 7,  "qq1": "0329143924", "qq2": "3435842735", "message":} 
	//判断是否已经是好友了
	MYLOG("core::addfriendask");
	std::string jsonout;
	if (myado.findfriend(m.qq1, m.qq2) !=0  )
	{
		jsonout = js.jsonout(110, "已经是好友了");
	}
	else
	{
		//判断是否在线 
	struct	in_addr ip = getonline(m.qq2);
		if (ip.s_addr == 0)//不在线上，存入数据库
		{
			
			//放入数据库
			myado.insert(m.qq1, m.qq2,1, "", 0);
			jsonout = js.jsonout(110, "等待对方ing");
		}
		else//在线
		{
			jsonout = js.jsonout(114,m.qq1);
			return jsonout_ip{ ip, jsonout };
		}

	}
	
FL;
	return jsonout_ip{ m.ip,jsonout };

}

jsonout_ip core::addfriendreply(messagestruct &m)//回复添加qq好友
{
FL;
	//同意{  "type": 8,  "qq1": "3435842735", "qq2": "0329143924", "message":}  
	//不同意{  "type": 8,  "qq1": "3435842735", "qq2": "", "message":} 
	std::string jsonout;
	MYLOG("core::addfriendreply");
	if (m.qq2 != "")
	{
		myado.addfriend(m.qq1, m.qq2);//双向加好友的

		jsonout = js.jsonout(200, "");
		return jsonout_ip{ m.ip, jsonout };
	}
FL;
	return jsonout_ip();
}



jsonout_ip core::qqmessage(messagestruct &m)//qq消息
{/*
 qq消息测试
 {  "type": 2,  "qq1": "3756456092", "qq2": "", "message": {"pass": "123" }}
 {  "type": 6,  "qq1": "0329143924", "qq2": "3756456092", "message": {"mess":"zhe shi qq message"}}

 {  "type": 6,  "qq1": "0329143924", "qq2": "3435842735", "message": {"mess":"zhe shi qq message"}}
 */
FL;
	MYLOG("core::qqmessage");
	std::string jsonout;
	m.mess = js.readqqmessage(m.mess);
		//判断是否在线 
	struct	in_addr ip = getonline(m.qq2);
		if (ip.s_addr == 0)//不在线上，存入数据库
		{

			//放入数据库
			myado.insert(m.qq1, m.qq2, 2, m.mess, 0);

		}
		else//在线
		{
			jsonout = js.jsonout(115, m);
			return jsonout_ip{ ip, jsonout };
		}

FL;
	return jsonout_ip{ m.ip, jsonout };

}