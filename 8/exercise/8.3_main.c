#include"apue.h"
#include<sys/wait.h>

void print_siginfo(siginfo_t *infop);

int main(void){
	pid_t pid;
	int status;
	siginfo_t infop;

	//exit normally
	if((pid=fork())<0)
		err_sys("fork error");
	else if(pid==0)
		exit(7);

	if(waitid(P_ALL,pid,&infop,WEXITED|WSTOPPED)<0)
		err_sys("error waitid");
	print_siginfo(&infop);

	//generate signal SIGABRT
	if((pid=fork())<0)
		err_sys("fork error");
	else if(pid==0)
		abort();

	if(waitid(P_ALL,pid,&infop,WEXITED|WSTOPPED)<0)
		err_sys("error waitid");
	print_siginfo(&infop);

	//generate signal SIGFPE
	if((pid=fork())<0)
		err_sys("fork error");
	else if(pid==0)
		status /=0;

	if(waitid(P_ALL,pid,&infop,WEXITED|WSTOPPED)<0)
		err_sys("error waitid");
	print_siginfo(&infop);

	exit(0);
}

