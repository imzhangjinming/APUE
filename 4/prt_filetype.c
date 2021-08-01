#include"apue.h"

int main(int argc,char **argv){
	struct stat buf;
	char *pre;

	for(int i=0;i<argc;++i){
		printf("%s :",argv[i]);

		if(lstat(argv[i],&buf)==-1){
			err_sys("error lstat %s",argv[i]);
			continue;
		}

		if(S_ISREG(buf.st_mode))
			pre = "regular";
		else if(S_ISDIR(buf.st_mode))
			pre = "directory";	
		else if(S_ISCHR(buf.st_mode))
			pre = "character";	
		else if(S_ISBLK(buf.st_mode))
			pre = "block";	
		else if(S_ISFIFO(buf.st_mode))
			pre = "pipe/FIFO";	
		else if(S_ISLNK(buf.st_mode))
			pre = "symbolic link";	
		else if(S_ISSOCK(buf.st_mode))
			pre = "socket";	
		else 
			pre = "unknown file type";

		printf("%s\n",pre);
	}

	exit(0);
}
