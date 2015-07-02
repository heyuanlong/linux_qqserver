#include "conf.h"
#include "mylog.h"
#include <fstream>


mylog::mylog()
{
	fs.open("/qqserver/qqserver.log", std::fstream::in | std::fstream::out | std::fstream::app);
}


mylog::~mylog()
{
	fs.close();
}

void mylog::write(std::string str)
{

	fs << str;
	fs << std::endl;
}
/*
__FILE__ 文件名
__LINE__ 当前行号
*/