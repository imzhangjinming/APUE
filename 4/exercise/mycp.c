#include"apue.h"
#include<sys/types.h>
#include<unistd.h>
#include<fcntl.h>

static int mycp(const char *opathname,const char *npathname);

int main(int argc,char **argv){
	int ret;

	if(argc<3)
		err_quit("usage : mycp oldfile newfile");

	if((ret=mycp(argv[1],argv[2]))!=0)
		err_ret("error mycp %s %s",argv[1],argv[2]);

	exit(0);
}


static int mycp(const char *opathname,const char *npathname){
	int ofd,nfd;
	int old_begin_offset,old_end_offset,old_offset;
	int new_begin_offset,new_end_offset,new_offset;
	void *buf;
	struct stat old_stat;

	old_offset=0;
	old_end_offset=-2;
	
	if((lstat(opathname,&old_stat)<0))
		err_ret("error lstat %s",opathname);

	if((ofd=open(opathname,O_RDONLY))<0)
		err_ret("error open %s",opathname);

	if((nfd=creat(npathname,S_IRWXU|S_IRWXG|S_IRWXO))<0)
		err_ret("error open %s",npathname);

//old_offset<old_stat.st_size
	while((old_offset<old_stat.st_size)&&((old_begin_offset=lseek(ofd,0,SEEK_DATA))!=old_end_offset)){
		if(old_begin_offset==-1)
			err_ret("error lseek %s",opathname);

		new_begin_offset = old_begin_offset;

		if((old_end_offset=lseek(ofd,0,SEEK_HOLE))<0)
			err_ret("error lseek %s",opathname);
	
		if((buf=malloc((old_end_offset-old_begin_offset)))==NULL)
			err_sys("error malloc");

		if(lseek(ofd,old_begin_offset,SEEK_SET)<0)
			err_ret("error lseek %s",opathname);
		
		if(read(ofd,buf,old_end_offset-old_begin_offset)<0)
			err_ret("error read %s",opathname);

		if(lseek(ofd,old_end_offset,SEEK_SET)<0)
			err_ret("error lseek %s",opathname);
		
		if(lseek(nfd,new_begin_offset,SEEK_SET)<0)
			err_ret("error lseek %s",npathname);

		if(write(nfd,buf,old_end_offset-old_begin_offset)<0)
			err_ret("error read %s",opathname);
			
		free(buf);

		old_offset=old_end_offset;
	}
	
	close(ofd);
	close(nfd);

	return 0;	
}

