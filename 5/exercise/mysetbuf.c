#include"apue.h"

#ifdef __GLIBC__
#define _IO_UNBUFFERED 0x0002
#define _IO_LINE_BUF   0x0200
#endif

void mysetbuf(FILE *fp,char *buf);
int is_unbuffered(FILE *fp);
int is_linebuffered(FILE *fp);
void pr_buf_mode(const char *name,FILE *fp);

int main(void){
	FILE *fp=fopen("test","w");
	if(fp==NULL)
		err_sys("error fopen");

	char buf[BUFSIZ];

	mysetbuf(fp,NULL);
	pr_buf_mode("test",fp);	

	mysetbuf(fp,buf);
	pr_buf_mode("test",fp);	

	mysetbuf(stderr,buf);
	pr_buf_mode("stderr",stderr);	

	exit(0);
}

void mysetbuf(FILE *fp,char *buf){
	int len = BUFSIZ;
	struct stat stat_buf;
	int fd;

	if((fp==stderr)||(buf==NULL)){
		if(setvbuf(fp,buf,_IONBF,len)!=0)
			err_sys("error setvbuf _IONBF");

		printf("set to no buffer\n");
		return ;
	}

	fd = fileno(fp);

	if(fstat(fd,&stat_buf)==-1)
		err_sys("error fstat ");

	if(S_ISCHR(stat_buf.st_mode)||S_ISCHR(stat_buf.st_mode)||S_ISCHR(stat_buf.st_mode)||S_ISCHR(stat_buf.st_mode)){
		if(setvbuf(fp,buf,_IOLBF,len)!=0)
			err_sys("error setvbuf _IOLBF");

		printf("set to line buffer\n");
		return ;
	}else{
		if(setvbuf(fp,buf,_IOFBF,len)!=0)
			err_sys("error setvbuf _IOFBF");

		printf("set to full buffer\n");
		return ;
	}
}


int is_unbuffered(FILE *fp){ return fp->_flags&_IO_UNBUFFERED;}
int is_linebuffered(FILE *fp){ return fp->_flags&_IO_LINE_BUF;}

void pr_buf_mode(const char *name,FILE *fp){
	printf("%s: ",name);

	if(is_unbuffered(fp))
		printf("unbuffered\n");
	else if(is_linebuffered(fp))
		printf("line buffered\n");
	else
		printf("full buffered\n");

}
