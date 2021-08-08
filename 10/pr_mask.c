#include"apue.h"
#include<errno.h>

void pr_mask(const char *str){
	sigset_t sigset;
	int errno_save;

	sigemptyset(&sigset);

	errno_save = errno;
	if(sigprocmask(SIG_BLOCK,NULL,&sigset)<0)
		err_sys("error sigprocmask");
	else{
		printf("%s",str);
		if(sigismember(&sigset,SIGINT))
			printf(" SIGINT");
		if(sigismember(&sigset,SIGQUIT))
			printf(" SIGQUIT");
		if(sigismember(&sigset,SIGUSR1)){
			printf(" SIGUSR1");
			fflush(stdout);
		}
		if(sigismember(&sigset,SIGALRM))
			printf(" SIGALRM");

		printf("sigset = %d",sigset);
		printf("\n");
	}

	errno = errno_save;
}

