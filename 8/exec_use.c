#include"apue.h"
#include<unistd.h>
#include<sys/wait.h>

char *env_init[]={"USER=unknown","PATH=/home/ming/programming/APUE/8/",NULL};

int main(void){
	pid_t pid;

	if((pid=fork())<0)
		err_sys("error fork");
	else if(pid==0){
		if(execle("/home/ming/programming/APUE/8/echoall","echoall","myarg1","MY ARG2",(char *)0,env_init)<0)
			err_sys("error exevle");
	}

	if(waitpid(pid,NULL,0)<0)
		err_sys("error waitpid");

	if((pid=fork())<0)
		err_sys("error fork");
	else if(pid==0){
		sleep(2);
		if(execlp("/home/ming/programming/APUE/8/echoall","echoall","only 1 arg",(char *)0)<0)
			err_sys("error execlp");
	}

	exit(0);
}

