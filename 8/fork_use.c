#include"apue.h"
#include<unistd.h>

int gloval = 5;
char buf[]="a write to stdout";

int main(void){
	int var;
	pid_t pid;

	var=88;
	if(write(STDOUT_FILENO,buf,sizeof(buf)-1)!=(sizeof(buf)-1))
		err_sys("error write buf");

	printf("before fork\n");

	if((pid=fork())<0)
		err_sys("error fork");
	else if(pid==0){
		gloval++;
		var++;
	}else
		sleep(2);

	printf("pid = %ld, glob = %d,var = %d\n",pid,gloval,var);

	exit(0);
}
