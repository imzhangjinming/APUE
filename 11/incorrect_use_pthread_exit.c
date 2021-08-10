#include"apue.h"
#include<pthread.h>

struct foo{
	int a,b,c,d;
};

void printfoo(const char *s,const struct foo *fp){
	printf("%s",s);
	printf(" structure at 0x%lx\n",(unsigned long)fp);
	printf(" foo.a = %d\n",fp->a);
	printf(" foo.b = %d\n",fp->b);
	printf(" foo.c = %d\n",fp->c);
	printf(" foo.d = %d\n",fp->d);
}

void *thr_fcn1(void *arg){
	struct foo foo={1,2,3,4};

	printfoo("thread 1:\n",&foo);
	pthread_exit((void*)&foo);
}

void *thr_fcn2(void *arg){
	printf("thread 2: ID is %lu\n",(unsigned long)pthread_self());
	pthread_exit((void*)0);
}

int main(void){
	pthread_t tid1,tid2;
	int err;
	struct foo* fp;

	err=pthread_create(&tid1,NULL,thr_fcn1,NULL);
	if(err!=0)
		err_exit(err,"can't create thread");
	err=pthread_join(tid1,(void*)&fp);
	if(err!=0)
		err_exit(err,"can't join thread1");

	sleep(1);

	printf("parent starting thread 2\n");

	err=pthread_create(&tid2,NULL,thr_fcn2,NULL);
	if(err!=0)
		err_exit(err,"can't create thread");

	sleep(1);
	printfoo("parent:\n",fp);

	exit(0);
}



