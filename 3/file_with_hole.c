#include "apue.h"
#include<fcntl.h>

int main(void){
	int fd;

	char buf1[]="ABCDE";
	char buf2[]="abcde";

	if((fd=creat("file_with.hole",FILE_MODE))<0)
		err_sys("creat error");
	//now the offset is 0

	if(write(fd,buf1,5)!=5)
		err_sys("buf1 write error");
	//now the offset is 5
	
	if(lseek(fd,100,SEEK_CUR)==-1)
		err_sys("lseek error");
	//now the offset is 105
	
	if(write(fd,buf2,5)!=5)
		err_sys("buf2 write error");
	//now the offset is 110
	
	exit(0);
}
	
	
