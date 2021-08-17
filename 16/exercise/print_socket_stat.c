#include"apue.h"
#include<sys/stat.h>
#include<sys/socket.h>

void print_stat(struct stat *buf);



void print_stat(struct stat *buf){
	printf(" file type: ");
	if(S_ISSOCK(buf->st_mode))
		printf("socket");
	else
		printf("not socket");

	printf("\nuid: %d gid: %d",buf->st_uid,buf->st_gid);

	printf("\nnumber of blocks allocated: %d",buf->st_blocks);

	printf("\nsize in bytes: %d",buf->st_size);
}

int main(void){
	int sockfd;
	struct stat buf;

	printf("AF_INET SOCK_DGRAM\n");

	if((sockfd=socket(AF_INET,SOCK_DGRAM,0))<0)
		err_sys("socket error AF_INET SOCK_DGRAM");

	if(fstat(sockfd,&buf)<0)
		err_sys("fstat error");

	print_stat(&buf);


//	printf("AF_INET SOCK_SEQPACKET\n");

//	if((sockfd=socket(AF_INET,SOCK_SEQPACKET,0))<0)
//		err_sys("socket error AF_INET SOCK_SEQPACKET");

//	if(fstat(sockfd,&buf)<0)
//		err_sys("fstat error");

//	print_stat(&buf);
	
	printf("\nAF_INET SOCK_STREAM\n");

	if((sockfd=socket(AF_INET,SOCK_STREAM,0))<0)
		err_sys("socket error AF_INET SOCK_STREAM");

	if(fstat(sockfd,&buf)<0)
		err_sys("fstat error");

	print_stat(&buf);

	exit(0);
}
