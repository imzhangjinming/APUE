#include"apue.h"
#include<fcntl.h>
#include<sys/wait.h>

void TELLWAIT(void);
void TELL_PARENT(pid_t);
void WAIT_PARENT(void);
void TELL_CHILD(pid_t);
void WAIT_CHILE(void);


int main(void){
	FILE *fp;
	pid_t pid;
	int i=0,j=0;
	static int count=0;


	if((fp=fopen("./temp.foo","a"))==NULL)
		err_sys("error fopen");

	if(fprintf(fp,"%d\n",count)<0){
		err_sys("error write 0");
	}

	fflush(NULL);

	count+=1;

	TELLWAIT();
	if((pid=fork())<0)
		err_sys("fork error");
	else if(pid==0){
		for(;i<20;i++){
			if(fprintf(fp,"%d",count)<0){
				err_ret("error write %d",count);
			}

			fflush(NULL);

			count+=2;

			if(fprintf(fp,"%s"," child wrote\n")<0)
				err_sys("error write ");

			fflush(NULL);

			TELL_PARENT(getppid());
			WAIT_PARENT();
		}
		TELL_PARENT(getppid());
		exit(0);
	}else{
		WAIT_CHILD();
		for(count=0;j<20;j++){
			
			count+=2;

			if(fprintf(fp,"%d",count)<0){
				err_ret("error write %d",count);
			}

			fflush(NULL);

			if(fprintf(fp,"%s"," parent wrote\n")<0)
				err_sys("error write ");

			fflush(NULL);

			TELL_CHILD(pid);
			WAIT_CHILD();
		}
	}

	if(waitpid(pid,NULL,0)!=pid)
		err_sys("error waitpid");

	fclose(fp);

	exit(0);
}
