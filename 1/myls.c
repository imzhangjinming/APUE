#include "apue.h"
#include<dirent.h>

int main(int argc,char ** argv){
	DIR *dp;
	struct dirent *dirp;

	if(argc!=2)
		printf("usage: ./a.out directory_name\n");

	if((dp=opendir(argv[1]))==NULL)
		err_quit("can't open %s\n",argv[1]);

	while((dirp=readdir(dp))!=NULL)
		printf("%s\n",dirp->d_name);

	closedir(dp);
	exit(0);
}
