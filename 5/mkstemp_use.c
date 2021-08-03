#include"apue.h"
#include<errno.h>

int main(void){
	char good_template[]="/tmp/dirXXXXXX";
	char *bad_template="/tmp/dirXXXXXX";
	int fd1;
	int fd2;
	struct stat f1,f2;

	printf("trying to create first tmp file...\n");
	if((fd1=mkstemp(good_template))==-1)
		err_sys("error mkstemp file 1");

	if(stat(good_template,&f1)==-1)
		if(errno==ENOENT)
			err_sys("file1 doesn't exist");
		else
			err_sys("error stat file1");
	else{ 
		printf("file1 exist: %s\n",good_template);
		unlink(good_template);
	}
	
	printf("trying to create second tmp file...\n");
	if((fd2=mkstemp(bad_template))==-1)
		err_sys("error mkstemp file 2");
	
	if(stat(bad_template,&f1)==-1)
		if(errno==ENOENT)
			err_sys("file2 doesn't exist");
		else
			err_sys("error stat file2");
	else{ 
		printf("file2 exist: %s\n",bad_template);
		unlink(bad_template);
	}

	exit(0);
}
