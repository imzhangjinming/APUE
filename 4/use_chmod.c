#include"apue.h"

int main(void){
	struct stat buf;

	if(stat("./foo",&buf)==-1)
		err_sys("error stat foo");

	//turn on set_group_ID and turn off group write 
	
	if(chmod("./foo",(buf.st_mode & ~S_IWGRP)|S_ISGID)==-1)
		err_sys("error chmod foo");

	exit(0);
}
		
