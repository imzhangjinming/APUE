#include"apue.h"
#include<pwd.h>
#include<errno.h>

struct passwd *mygetpwnam(const char *name);

int main(int argc,char **argv){
	if(argc < 2)
		err_quit("usage : mygetpwnam username");

	struct passwd *ptr;

	errno=0;

	if((ptr=mygetpwnam(argv[1]))==NULL)
		if(errno==0)
			err_sys("no such user");
		else
			err_sys("error mygetpwnam");

	printf("username: 		%s\n",ptr->pw_name);
	printf("encrypted passwd: 	%s\n",ptr->pw_passwd);
	printf("user id: 		%d\n",ptr->pw_uid);
	printf("group id: 		%d\n",ptr->pw_gid);
	printf("comment: 		%s\n",ptr->pw_gecos);
	printf("initial working dir: %s\n",ptr->pw_dir);
	printf("initial shell: 	%s\n",ptr->pw_shell);

	return 0;
}

struct passwd *mygetpwnam(const char *name){
	struct passwd *ptr;

	setpwent();
	while((ptr=getpwent())!=NULL)
		if(strcmp(name,ptr->pw_name)==0)
			break;

	endpwent();

	return ptr;
}

