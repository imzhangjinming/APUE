#include "apue.h"

int main(void){
	if(lseek(STDIN_FILENO,0,SEEK_SET)==-1)
		printf("can not seek\n");
	else
		printf("seek OK\n");

	return 0;
}
