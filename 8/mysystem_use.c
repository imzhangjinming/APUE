#include"apue.h"
#include<sys/wait.h>

int main(void){
	int status;

	if((status=system("date"))<0)
		err_sys("error system date");

	if((status=system("nosuchcommand"))<0)
		err_sys("error system nosuchcommand");

	if((status=system("who; exit 44"))<0)
		err_sys("error system who; exit 44");

	exit(0);
}
