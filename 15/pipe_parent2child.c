#include"apue.h"

int main(void){
	char line[MAXLINE];
	ssize_t n;
	pid_t pid;
	int fd[2];

	if(pipe(fd)<0)
		err_sys("pipe error");

	if((pid=fork())<0)
		err_sys("fork error");
	else if(pid>0){
		close(fd[0]);
		write(fd[1],"hello world",12);
	}else{
		close(fd[1]);
		n = read(fd[0],line,MAXLINE);
		write(STDOUT_FILENO,line,n);
	}

	exit(0);
}

