#ifndef CONF_H
#define CONF_H


//----------------------加上一对花括号是为了在同一个函数里可以使用多个带定义的MYLOG，不同作用域了
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