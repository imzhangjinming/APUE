#include"apue.h"
#include<signal.h>

static void my_catch(int signo);

int main(void){
	if(signal(SIGUSR1,my_catch)==SIG_ERR)
		err_sys("signal error");

	if(signal(SIGUSR2,my_catch)==SIG_ERR)
		err_sys("signal error");
	
	while(1)
		pause();

	exit(0);
}

static void my_catch(int signo){
	if(signo==SIGUSR1)
		printf("received SIGUSR1\n");
	else if(signo==SIGUSR2)
		printf("received SIGUSR2\n");
	else 
		printf("received signal %d\n",signo);
}
		


