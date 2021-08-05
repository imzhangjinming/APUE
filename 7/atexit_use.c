#include"apue.h"
#include<stdlib.h>

void exit_handler_1(void);
void exit_handler_2(void);

int main(void){
	if(atexit(exit_handler_1)!=0)
		err_sys("error atexit exit handler 1");

	if(atexit(exit_handler_2)!=0)
		err_sys("error atexit exit handler 2");

	if(atexit(exit_handler_1)!=0)
		err_sys("error atexit exit handler 1");

	printf("main is done\n");

	exit(0);
}

void exit_handler_1(void){
	printf("exit handler 1 called\n");
}

void exit_handler_2(void){
	printf("exit handler 2 called\n");
}
