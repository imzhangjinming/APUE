#include"apue.h"
#include<pthread.h>

pthread_t ntid;

void printids(void *s){
	pid_t pid;
	pthread_t tid;

	pid = getpid();
	tid = pthread_self();
	printf("%s pid %lu tid %lu (0x%lx)\n",s,pid,tid,tid);
}

void *thr_fcn(void *arg){
	printids("new thread: ");
	return ((void*)0);
}

int main(void){
	int err;

	err=pthread_create(&ntid,NULL,thr_fcn,NULL);
	if(err!=0)
		err_exit(err,"can't create thread");

	printids("main thread: ");

	/* 令主线程休眠，防止主线程退出 */
	sleep(1);

	exit(0);
}
