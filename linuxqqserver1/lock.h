#ifndef LOCK_H
#define LOCK_H

#include <pthread.h>

pthread_mutex_t mutex[4] = {PTHREAD_MUTEX_INITIALIZER,
							PTHREAD_MUTEX_INITIALIZER,
							PTHREAD_MUTEX_INITIALIZER,
							PTHREAD_MUTEX_INITIALIZER};


//丫的，哪里pthread_mutex_destroy它们合适？？？

inline void lock12()
{
	//FL;
  pthread_mutex_lock(&mutex[0]);
  //FL;
}
inline void unlock12()
{//FL;
  pthread_mutex_unlock(&mutex[0]);
  //FL;
}

inline void lock23()
{//FL;
  pthread_mutex_lock(&mutex[1]);
//FL;
}
inline void unlock23()
{//FL;
  pthread_mutex_unlock(&mutex[1]);
  //FL;
}

inline void lock24()
{//FL;
  pthread_mutex_lock(&mutex[2]);
  //FL;
}
inline void unlock24()
{//FL;
  pthread_mutex_unlock(&mutex[2]);
  //FL;
}

inline void lock36()
{//FL;
  pthread_mutex_lock(&mutex[3]);
  //FL;
}
inline void unlock36()
{//FL;
  pthread_mutex_unlock(&mutex[3]);
  //FL;
}


/*
void lock12push()
{
  pthread_mutex_lock(&mutex[0]);
  ++lock_mutex_number[0];
}
bool lock12pop()
{
  pthread_mutex_lock(&mutex[0]);
  --lock_mutex_number[0];
  if (lock_mutex_number[0] < 0)
  {
  	lock_mutex_number[0]=0;
  	return false;
  }
  return true;
}
void unlock12()
{
  pthread_mutex_lock(&mutex[0]);
}



void lock23push()
{
  pthread_mutex_lock(&mutex[1]);
  ++lock_mutex_number[1];
}
bool lock23pop()
{
  pthread_mutex_lock(&mutex[1]);
  --lock_mutex_number[1];
  if (lock_mutex_number[1] < 0)
  {
  	lock_mutex_number[1]=0;
  	return false;
  }
  return true;
}
void unlock23()
{
  pthread_mutex_lock(&mutex[1]);
}




void lock24push()
{
  pthread_mutex_lock(&mutex[2]);
  ++lock_mutex_number[2];
}
bool lock24pop()
{
  pthread_mutex_lock(&mutex[2]);
  --lock_mutex_number[2];
  if (lock_mutex_number[2] < 0)
  {
  	lock_mutex_number[2]=0;
  	return false;
  }
  return true;
}
void unlock24()
{
  pthread_mutex_lock(&mutex[2]);
}





void lock36push()
{
  pthread_mutex_lock(&mutex[3]);
  ++lock_mutex_number[3];
}
bool lock36pop()
{
  pthread_mutex_lock(&mutex[3]);
  --lock_mutex_number[3];
  if (lock_mutex_number[3] < 0)
  {
  	lock_mutex_number[3]=0;
  	return false;
  }
  return true;
}

void unlock36()
{
  pthread_mutex_lock(&mutex[3]);
}

*/







#endif
