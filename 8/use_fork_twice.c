#include"apue.h"
#include<unistd.h>
#include<sys/wait.h>

int main(void){
	pid_t pid;

	if((pid=fork())<0)
		err_sys("error fork");
	else if(pid==0){
		if((pid=fork())<0)
			err_sys("error fork 2");
		else if(pid > 0)
			exit(0);

		sleep(2);
		printf("second child,parent pid = %ld\n",(long)getppid());
		exit(0);
	}

	if(waitpid(pid,NULL,0)!=pid)
		err_sys("error waitpid");

	exit(0);
}
