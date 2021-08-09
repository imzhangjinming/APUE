#include"apue.h"
#include<pthread.h>

void *thr_fcn1(void *arg){
	printf("new thread1 exist\n");
	pthread_exit((void*)1);
}

void *thr_fcn2(void *arg){
	printf("new thread2 exist\n");
	pthread_exit((void*)2);
}

int main(void){
	int err;
	pthread_t tid1,tid2;
	void *tret;

	err=pthread_create(&tid1,NULL,thr_fcn1,NULL);
	if(err!=0)
		err_exit(err,"can't create new thread");

	err=pthread_create(&tid2,NULL,thr_fcn2,NULL);
	if(err!=0)
		err_exit(err,"can't create new thread");

	err=pthread_join(tid1,&tret);
	if(err!=0)
		err_exit(err,"can't join thread 1");
	printf("thread1 exit code %ld\n",(long)tret);

	err=pthread_join(tid2,&tret);
	if(err!=0)
		err_exit(err,"can't join thread 2");
	printf("thread2 exit code %ld\n",(long)tret);

	exit(0);
}
