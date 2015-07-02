#makefile
.PHONY:clean 
#防止clean时出错而中断

qqserver:qqserver.o center.o communication.o myjson.o core.o ado.o mylog.o jyjson/value.o jyjson/read.o jyjson/write.o
	g++ -std=c++11 qqserver.o center.o communication.o myjson.o core.o ado.o mylog.o jyjson/value.o jyjson/read.o jyjson/write.o -o qqserver -L/usr/lib/mysql -lmysqlclient -lpthread

qqserver.o:qqserver.h qqserver.cpp center.h daemon.h 
	g++ -c qqserver.cpp -o qqserver.o

center.o:center.h center.cpp conf.h  communication.h myjson.h messagestruct.h core.h lock.h 
	g++ -c center.cpp -o center.o -I/usr/include/mysql -L/usr/lib/mysql -lmysqlclient -lpthread

communication.o:communication.h communication.cpp messagestruct.h lock.h conf.h center.h
	g++ -c communication.cpp -std=c++11 -o communication.o 

myjson.o:myjson.h myjson.cpp messagestruct.h conf.h 
	g++ -c myjson.cpp -o myjson.o 

jyjson/value.o:jyjson/value.cpp jyjson/value.h jyjson/jsexcept.h
	g++ -c -std=c++11 jyjson/value.cpp -o jyjson/value.o
jyjson/read.o:jyjson/read.cpp jyjson/read.h
	g++ -c -std=c++11 jyjson/read.cpp -o jyjson/read.o
jyjson/write.o:jyjson/write.cpp jyjson/write.h
	g++ -c -std=c++11 jyjson/write.cpp -o jyjson/write.o

core.o:core.h core.cpp conf.h myjson.h ado.h messagestruct.h
	g++ -c core.cpp -o core.o -std=c++11 -I/usr/include/mysql -L/usr/lib/mysql -lmysqlclient
ado.o:ado.h ado.cpp messagestruct.h conf.h
	g++ -c ado.cpp -o ado.o -I/usr/include/mysql -L/usr/lib/mysql -lmysqlclient
mylog.o:mylog.h mylog.cpp conf.h
	g++ -c mylog.cpp -o mylog.o


clean:#可以在命令中输入 make clean 来执行这个规则
	$(RM) *.o qqserver