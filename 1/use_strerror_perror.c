#include"apue.h"
#include<errno.h>

int main(void){
	printf("EACCES: %s\n",strerror(EACCES));
	errno=ENOENT;
	perror("test");
	exit(0);
}
