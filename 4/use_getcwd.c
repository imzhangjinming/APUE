#include"apue.h"

int main(void){
	char *ptr;
	size_t size;

	ptr = path_alloc(&size);
	if(getcwd(ptr,size)==NULL)
		err_sys("error getcwd");

	printf("cwd = %s\n",ptr);
	exit(0);
}
