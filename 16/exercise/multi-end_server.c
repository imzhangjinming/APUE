#include"apue.h"
#include<sys/socket.h>
#include<netdb.h>
#include<errno.h>
#include<syslog.h>
#include<sys/select.h>

#define BUFLEN 128
#define QLEN 10
#define MAX_ENDPOINTS 64

#ifndef HOST_NAME_MAX
#define HOST_NAME_MAX 26
#endif

extern int initserver(int,const struct sockaddr *,socklen_t,int);

void serve_many(int sockfd[],int numsockfd){
	int clfd;
	FILE *fp;
	char buf[BUFLEN];
	fd_set readsfds,set;
	int i,maxsock=0;

	FD_ZERO(&readsfds);
	for(i=0;i<numsockfd;i++){
		set_cloexec(sockfd[i]);
		FD_SET(sockfd[i],&readsfds);
		if(sockfd[i]>maxsock)
			maxsock=sockfd[i];
	}

	for(;;){
		set = readsfds;
		select(maxsock+1,&set,NULL,NULL,NULL);
		
		for(i=0;i<numsockfd;i++){
			if(FD_ISSET(sockfd[i],&set){
				if((clfd=accept(sockfd[i],NULL,NULL))<0){
					syslog(LOG_ERR,"ruptimed:accept error: %s",strerror(errno)); 
					exit(0);
				}
				set_cloexec(clfd);


				if((fp=popen("/usr/bin/uptime","r"))==NULL){
					sprintf(buf,"error: %s\n",strerror(errno));
					send(clfd,buf,strlen(buf),0);
				}else{
					while(fgets(buf,BUFLEN,fp)!=NULL)
						send(clfd,buf,strlen(buf),0);
					pclose(fp);
				}

				close(clfd);
			}
		}
	}
}

int main(int argv,char **argv){
	struct addrinfo *ailist,*aip;
	struct addrinfo hint;
	int sockfd,err,n,nendpoints=0;
	int endpoints[MAX_ENDPOINTS];
	char *host;

	if(argc!=1)
		err_quit("usage: ruptimed");

	if((n=sysconf(_SC_HOST_NAME_MAX))<0)
		n=HOST_NAME_MAX;

	if((host=malloc(n))==NULL)
		err_sys("malloc error");

	if(gethostname(host,n)<0)
		err_sys("gethost name error");

	daemonize("ruptimed");
	memset(&hint,0,sizeof(hint));
	hint.ai_flags=AI_CANONNAME;
	hint.ai_socktype=SOCK_STREAM;
	hint.ai_canonname=NULL;
	hint.ai_addr=NULL;
	hint.ai_next=NULL;
	if((err=getaddrinfo(host,"ruptime",&hint,&ailist))!=0){
		syslog(LOG_ERR,"ruptimed: getaddrinfo error : %s",gai_strerror(err));
		exit(1);
	}

	for(aip=ailist;aip!=NULL;aip=aip->ai_next){
		if((sockfd=initserver(SOCK_STREAM,aip->ai_addr,aip->ai_addrlen,QLEN))>=0){
			endpoints[nendpoints++]=sockfd;
		}
	}

	if(nendpoints){
		serve_many(endpoints,nendpoints);
		exit(0);
	}else{
		fprintf(stderr,"No endpoint to serve on");
		exit(1);
	}
}

