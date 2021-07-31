#include"apue.h"
#include<errno.h>
#include<fcntl.h>
#include<unistd.h>

int main(void){
	char buf1[] = "ABCDEFGHIJK";
	char read_from_start[5];
	char write_at_start[]="abcde";
	int fd;

	if((fd=creat("./test",O_RDWR))==-1)
		err_sys("error creat O_RDWR");

	if(write(fd,buf1,12)!=12)
		err_sys("error write buf1");

	close(fd);

	if((fd=open("./test",O_APPEND))==-1)
		err_sys("error open ./test");

	if(lseek(fd,0,SEEK_SET)==-1)
		err_sys("error lseek ./test");

	if(read(fd,read_from_start,4)==-1)
		err_sys("error read from start");

	read_from_start[4]='\0';

	printf("%s\n",read_from_start);

	if(write(fd,write_at_start,5)==-1)
		err_sys("error write at start");

	printf("%s\n",buf1);

	return 0;
}
