#include"apue.h"

int main(void){
	if(chdir("../")<0)
		err_sys("error chdir ../");

	printf("chdir to ../ succeeded");

	exit(0);
}
