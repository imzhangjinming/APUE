#include"apue.h"
#include<sys/wait.h>

#define PAGER "${PAGER:-more}"

int main(int argc,char **argv){
	FILE *fpin,*fpout;
	char line[MAXLINE];

	if(argc!=2)
		err_quit("usage: ./a.out <pathname>");

	if((fpin=fopen(argv[1],"r"))==NULL)
		err_sys("foprn error");

	if((fpout=popen(PAGER,"w"))==NULL)
		err_sys("popen error");

	while(fgets(line,MAXLINE,fpin)!=NULL){
		if(fputs(line,fpout)==EOF)
			err_sys("fputs error to pipe");
	}

	if(ferror(fpin))
		err_sys("fgets error");
	
	if(pclose(fpout)==-1)
		err_sys("pclose error");

	exit(0);
}	
	
