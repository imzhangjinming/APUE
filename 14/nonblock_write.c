#include"apue.h"
#include<errno.h>
#include<fcntl.h>

char buf[100000];

int main(void){
	int ntowrite,nwrite;
	char *ptr;

	if((ntowrite=read(STDIN_FILENO,buf,sizeof(buf)))<0)
		err_sys("read error");
	fprintf(stderr,"read %d bytes\n",ntowrite);

	set_fl(STDOUT_FILENO,O_NONBLOCK);

	ptr=buf;
	while(ntowrite>0){
		errno=0;

		nwrite=write(STDOUT_FILENO,ptr,ntowrite);
		fprintf(stderr,"nwrite = %d, errno = %d\n",nwrite,errno);

		if(nwrite>0){
			ptr+=nwrite;
			ntowrite-=nwrite;
		}
	}

	clr_fl(STDOUT_FILENO,O_NONBLOCK);

	exit(0);
}
