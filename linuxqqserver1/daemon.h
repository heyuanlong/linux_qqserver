#ifndef DAEMON_H
#define DAEMON_H

#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>

int daemon()
{
	switch(fork())
	{
		case -1:
			return -1;
		case 0:
			break;
		default:
			_exit(0);//父进程退出
	}
	if (setsid() == -1)
		return -1;
	if (chdir("/") !=0)
	{
		perror("chdir");
		return -1;
	}

	int fd;
	if (umask(0) == -1) 
	{
			perror("umask");
			return -1;
	}

	if ((fd=open("/qqserver/io.txt",O_WRONLY | O_CREAT | O_APPEND,0600)) != -1)
	{
		if (dup2(fd,STDIN_FILENO) < 0)
		{
			perror("dup2 stdin");
			return -1;
		}
		if (dup2(fd,STDOUT_FILENO) < 0)
		{
			perror("dup2 stdout");
			return -1;
		}
		if (dup2(fd,STDERR_FILENO) < 0)
		{
			perror("dup2 stderr");
			return -1;
		}

		if (fd > STDERR_FILENO)
		{
			if(close(fd) < 0){  //关闭fd
				perror("close");
				return -1;
			}
		}
	}

	return 0;
}


#endif
