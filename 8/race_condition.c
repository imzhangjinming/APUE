#include"apue.h"

static void print_string(char *);

int main(void){
	pid_t pid;
	if((pid=fork())<0)
		err_sys("error fork");
	else if(pid==0)
		print_string("print from child\n");
	else 
		print_string("print from parent\n");


	exit(0);
}

static void print_string(char *src){
	char *ptr;
	int c;

	setbuf(stdout,NULL);

	for(ptr=src;(c=*ptr++)!=0;)
		putc(c,stdout);

}


