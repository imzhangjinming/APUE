#include "apue.h"

#define BUFFERSIZE 4096

int main(void){
	int n;
	char buff[BUFFERSIZE];

	while((n=read(STDIN_FILENO,buff,BUFFERSIZE))>0){
		if(write(STDOUT_FILENO,buff,n)!=n)
			err_sys("write error\n");
	}

	if(n<0)
		err_sys("read error\n");

	exit(0);
}
