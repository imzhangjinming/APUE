#include<sys/socket.h>

int init_server_socket(int type,struct sockaddr *addr,socklen_t alen,int qlen){
	int fd;
	int err=0;

	if((fd=socket(addr->sa_family,type,0))<0)
		return (-1);

	if(bind(fd,addr,alen)<0)
		goto errout;

	if(type==SOCK_STREAM||type == SOCK_SEQPACKET){
		if(listen(fd,qlen)<0)
			goto error;
	}

	return (fd);

errout:
	err=errno;
	close(fd);
	errno=err;
	return (-1);
}
