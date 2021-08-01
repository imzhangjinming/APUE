#include"apue.h"
#include<unistd.h>
#include<fcntl.h>

int main(void){
	if(open("tempfile",O_RDWR|O_CREAT)<0)
		err_sys("error open tempfile");

	if(unlink("tempfile")<0)
		err_sys("error unlink tempfile");

	sleep(15);

	exit(0);
}
