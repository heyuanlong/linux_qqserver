#include "qqserver.h"
#include "center.h"
#include "daemon.h"

#include <iostream>
#include <unistd.h>
#include <stdio.h>
#include <errno.h>


int main(int argc, char const *argv[])
{
center cen;
bool do_daemonize = false;

	if (do_daemonize == true)
	 	if(-1 == daemon())//��Ϊ�ػ�������������ض����ˣ�����
	 	{
	 		std::cerr<<"failed to daemon() in order to daemonize\n";
	 	}

	if (cen.run() == false)
	{
		std::cerr<<"failed to cen.run() in order to run\n";
	}
	while(1);
	return 0;
}

/*
std::cerr���������
MYLOG ��������־

*/


