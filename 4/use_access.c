#include"apue.h"
#include<unistd.h>

int main(int argc, char **argv){
	if(argc<2){
		printf("usage: ./a.out <pathname>\n");
		return 0;
	}

	if(access(argv[1],R_OK)==-1)
		err_sys("error access R_OK");
	else
		printf("read OK");

	exit(0);
}
