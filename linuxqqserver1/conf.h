#ifndef CONF_H
#define CONF_H


//----------------------����һ�Ի�������Ϊ����ͬһ�����������ʹ�ö���������MYLOG����ͬ��������
#define LOG 1
	#ifdef LOG
		 #include "mylog.h"
		 #define MYLOG(expr) {mylog logg;\
			logg.write(expr); }
	#else
	 	#define MYLOG(expr)
	#endif 

#define DEBUG 1
	#ifdef DEBUG
		#define FL std::cout<<__FILE__<<":"<<__LINE__<<std::endl
	#endif 
  
#endif