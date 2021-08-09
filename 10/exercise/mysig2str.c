#include<string.h>
#include<signal.h>
#include"apue.h"
#include<stdlib.h>
#include<stdio.h>

#define GUESS_MAX 256
int mysig2str(int signo,char *str){
	if(str==NULL)
		return -1;

	strcpy(str,strsignal(signo));

	return 0;
}

int main(int argc,char **argv){
	if(argc<2)
		err_quit("usage: ./a.out signo");
#ifdef SIG2STR_MAX 
	char *str = malloc(SIG2STR_MAX*sizeof(char));
#else 
	char *str = malloc(GUESS_MAX*sizeof(char));
#endif
	
	if(mysig2str(atoi(argv[1]),str)<0)
		err_sys("error mysig2str");

	printf("%d : %s\n",atoi(argv[1]),str);

	exit(0);
}
