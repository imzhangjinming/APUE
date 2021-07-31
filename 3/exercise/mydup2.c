#include"apue.h"
#include<limits.h>
#include<errno.h>

#ifdef OPEN_MAX
static int openmax = OPEN_MAX;
#else
static int openmax = 0;
#endif

#define OPEN_MAX_GUESS 256

int mydup2(int fd, int fd2){
	int openmax=0;

	if(fd==fd2)
		return fd;

	if(openmax==0){
		errno=0;
		if((openmax=sysconf(_SC_OPEN_MAX))==-1){
			if(errno==0)
				openmax = OPEN_MAX_GUESS;
			else
				err_sys("sysconf error _SC_OPEN_MAX");
		}
	}

	if(fd<0 || fd>openmax || fd2<0 || fd2 > openmax){
		errno=EBADF;
		return -1;	
	}

	close(fd2);

	int *fd_list = malloc(openmax*sizeof(int));
	int fd_total = 0;

	while((fd_list[fd_total]=dup(fd))!=fd2)
		fd_total++;

	while(--fd_total!=0)
		close(fd_list[fd_total]);

	free(fd_list);

	return fd2;
}

int main(void){
	if(mydup2(STDOUT_FILENO,15)<0)
		err_sys("error mydup2 STDOUT_FILENO");

	if(write(15,"Hello World.\n",14)!=14)
		err_sys("error write");

	return 0;
}
