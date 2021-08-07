#include"apue.h"
#include<sys/wait.h>

void print_siginfo(siginfo_t *infop){
	switch(infop->si_code){
		case CLD_EXITED:printf("normal termination,exit status = %d\n",\
								infop->si_status);
						break;
		case CLD_KILLED:printf("child killed by signal ,signal number = %d\n",\
								infop->si_status);
						break;
		case CLD_DUMPED:printf("child killed by signal,and dumped core,\
								signal number = %d (core file generated)\n",\
								infop->si_status);
						break;
		case CLD_STOPPED:printf("child stopped by signal,signal number = %d\n",\
								 infop->si_status);
						 break;
		case CLD_TRAPPED:printf("traced child has trapped,signal number = %d\n",\
								 infop->si_status);
						 break;
		case CLD_CONTINUED:printf("child continued by SIGCONT\n");
						   break;
		default:printf("unknown exit status,si_code = %d\n",infop->si_code);
	}
}

								
