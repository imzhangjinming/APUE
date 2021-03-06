#include"apue.h"
#include<fcntl.h>
#include<syslog.h>
#include<sys/resource.h>

void daemonize(const char *cmd){
	struct rlimit rl;
	pid_t pid;
	struct sigaction sa;
	int i,fd0,fd1,fd2;

	// 清除文件创建屏蔽字
	umask(0);

	// 获得文件描述符的最大值
	if(getrlimit(RLIMIT_NOFILE,&rl)!=0)
		err_quit("%s:can't get file limit",cmd);

	// 第一次调用 fork 并让父进程退出
	if((pid=fork())<0)
		err_quit("%s:can't fork",cmd);
	else if(pid!=0)
		exit(0);
	setsid();

	sa.sa_handler=SIG_IGN;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags=0;
	if(sigaciton(SIGHUP,&sa,NULL)<0)
		err_quit("%s:can't ignore SIGHUP",cmd);
	if((pid=fork())<0)
		err_quit("%s:can't fork",cmd);
	else if(pid!=0)
		exit(0);

	if(chdir("/")<0)
		err_quit("%s: can't change directory to /",cmd);

	if(rl.rlim_max==RLIM_INFINITY)
		rl.rlim_max=1024;
	for(i=0;i<rl.rlim_max;i++)
		close(i);
	
	fd0=open("/dev/null",O_RDWR);
	fd1=dup(0);
	fd2=dup(0);

	openlog(cmd,LOG_CONS,LOG_DAEMON);
	if(fd0!=0||fd1!=1||fd2!=2){
		syslog(LOG_ERR,"unexpected file discriptors %d %d %d",fd0,fd1,fd2);
		exit(1);
	}
}	
