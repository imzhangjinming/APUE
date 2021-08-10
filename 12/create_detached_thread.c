#include<pthread.h>
#include"apue.h"

int create_detached_thread(void*(*fn)(void*),void *arg){
	pthread_attr_t attr;
	int err;
	pthread_t tid;

	err=pthread_attr_t(&attr);
	if(err!=0)
		return err;

	err=pthread_attr_setdetachstate(&attr,PTHREAD_CREATE_DETACHED);

	if(err==0)
		err=pthread_create(&tid,&attr,fn,arg);
	pthread_attr_destroy(&attr);

	return err;
}
