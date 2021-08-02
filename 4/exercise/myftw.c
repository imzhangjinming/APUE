#include"apue.h"
#include<dirent.h>
#include<limits.h>
#include<sys/stat.h>
#include<unistd.h>
#include<errno.h>

typedef int Cac(const char *pathname,const struct stat *statptr,int type); // Cac -- classify and count

static Cac classify_and_count;
static int dopath(Cac *cac);
static int myftw(const char *pathname,Cac *cac);

static long nreg,ndir,nblk,nchr,nfifo,nslink,nsock,ntot;

int main(int argc,char **argv){
	int ret;
	
	if(argc!=2)
		err_quit("usage: myftw <starting pathname>");

	ret = myftw(argv[1],classify_and_count);

	ntot = nreg+ndir+nblk+nchr+nfifo+nslink+nsock;

	if(ntot==0)
		ntot=1;

	printf("regular files 		= %7ld, %5.2f %%\n",nreg,nreg*100.0/ntot);
	printf("directory files 	= %7ld, %5.2f %%\n",ndir,ndir*100.0/ntot);
	printf("block files 		= %7ld, %5.2f %%\n",nblk,nblk*100.0/ntot);
	printf("character files 	= %7ld, %5.2f %%\n",nchr,nchr*100.0/ntot);
	printf("FIFO files		= %7ld, %5.2f %%\n",nfifo,nfifo*100.0/ntot);
	printf("symbolic link files	= %7ld, %5.2f %%\n",nslink,nslink*100.0/ntot);
	printf("socket files		= %7ld, %5.2f %%\n",nsock,nsock*100.0/ntot);

	exit(0);
}

static char *fullpath;
static char *old_path;
static size_t pathlen;

static int myftw(const char *pathname,Cac *cac){
	fullpath = path_alloc(&pathlen);
	old_path = path_alloc(&pathlen);

	if(pathlen<strlen(pathname)){
		pathlen = strlen(pathname)*2;
		if((fullpath=realloc(fullpath,pathlen))==NULL)
			err_sys("error realloc");
	}

	strcpy(fullpath,pathname);

	if(chdir(fullpath)<0)
		err_ret("error chdir %s",fullpath);

	return dopath(cac);
}

#define FTW_F 	1	// file
#define FTW_D 	2	// directory
#define FTW_DNR 3	// directory can not read
#define FTW_NS 	4	// file can not stat

static int dopath(Cac *cac){
	struct stat statbuf;
	int ret=0,n;
	DIR *dp;
	struct dirent *dirp;

//	if(lstat(fullpath,&statbuf)<0)
//		return(cac(fullpath,&statbuf,FTW_NS));
	
//	if(S_ISDIR(statbuf.st_mode)==0)	
//		return(cac(fullpath,&statbuf,FTW_F));

	// if fullpath is a directory, first cac(fullpath),
	// then recursively process each file in directory
	
//	strcpy(old_path,fullpath);

//	if(chdir(fullpath)<0)
//		err_ret("error chdir %s",fullpath);

//	if((ret=cac(fullpath,&statbuf,FTW_D))!=0)
//		return ret;
	
	//n=strlen(fullpath);

//	if(n+NAME_MAX+2>pathlen){
//		pathlen *= 2;
//		if((fullpath=realloc(fullpath,pathlen))==NULL)
//				err_sys("error realloc");
//	}
//
//	fullpath[n++]='/';
//	fullpath[n]=0;
//
	if((dp=opendir("./"))==NULL){
		err_sys("error opendir ./");
		return cac("./",&statbuf,FTW_DNR);
	}
	
	while((dirp=readdir(dp))!=NULL){
//		printf("processing %s\n",dirp->d_name);

		if(strcmp(dirp->d_name,".")==0 || strcmp(dirp->d_name,"..")==0)
			continue;

		if(lstat(dirp->d_name,&statbuf)<0){
			printf("errno: %d\n",errno);
			err_ret("error lstat %s",dirp->d_name);
			cac("./",&statbuf,FTW_NS);
		}

		if(S_ISDIR(statbuf.st_mode)==0){	
			cac("./",&statbuf,FTW_F);
			continue;
		}
		

		if((ret=cac("./",&statbuf,FTW_D))!=0){
			err_sys("error cac ./");
		}

		if(chdir(dirp->d_name)<0)
			err_ret("error chdir %s",dirp->d_name);
			
//		strcpy(fullpath,dirp->d_name);

		if((ret=dopath(cac))!=0)
			break;

		chdir(dirp->d_name);
		chdir("../");
//		printf("%s\n",dirp->d_name);
	}

//	fullpath[n-1]=0;

	if(closedir(dp)<0)
		err_ret("can't close directory %s","./");
	
//	if(chdir("../")<0)
//		err_sys("error chdir ../");

//	strcpy(fullpath,old_path);

//	printf("return from %s",dirp->d_name);
	return ret;
}


static int classify_and_count(const char *pathname,const struct stat *statptr,int type){
	switch(type){
		case FTW_F:
			switch(statptr->st_mode & S_IFMT){
				case S_IFREG: nreg++; break;
				case S_IFCHR: nchr++; break;
				case S_IFBLK: nblk++; break;
				case S_IFIFO: nfifo++; break;
				case S_IFLNK: nslink++; break;
				case S_IFSOCK: nsock++; break;
				default: break;
			}
			break;
				   
		case FTW_D: ndir++; break;
		case FTW_DNR: ndir++; break;
		case FTW_NS:  err_ret("stat error for %s",pathname); break;
		default : err_dump("unknown type %d for pathname %s",type,pathname); break;
	}
	return 0;
}
