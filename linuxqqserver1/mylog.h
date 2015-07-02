#ifndef MYLOG_H
#define MYLOG_H


#include <string>
#include <string.h>
#include <fstream>
class mylog
{
public:
	mylog();
	void write(std::string);
	virtual ~mylog();

	std::fstream fs;

};

#endif
