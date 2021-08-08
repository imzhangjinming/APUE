#include"apue.h"

static void sig_alrm(int signo){
	/* 什么也不做，只是返回唤醒 sigsuspend */
}

unsigned int reliable_sleep(unsigned int seconds){
	struct sigaction newact,oldact;
	sigset_t newmask,oldmask,suspmask;
	unsigned int unslept;

	/* 设置信号处理函数并保存之前的设置 */
	newact.sa_handler=sig_alrm;
	sigemptyset(&newact.sa_mask);
	newact.sa_flags=0;
	sigaction(SIGALRM,&newact,&oldact);

	/* 阻塞 SIGALRM 信号并保存现在的 信号屏蔽字 */
	sigemptyset(&newmask);
	sigaddset(&newmask,SIGALRM);
	sigprocmask(SIG_BLOCK,&newmask,&oldmask);

	alarm(seconds);

	suspmask=oldmask;
	sigdelset(&suspmask,SIGALRM);

	sigsuspend(&suspmask);

	/* 有信号被捕捉到并且从信号处理函数返回，此时 SIGALRM 信号已经解除阻塞 */
	unslept=alarm(0);

	/* 将 SIGALRM 信号的操作恢复 */
	sigaction(SIGALRM,&oldact,NULL);

	/* 将信号屏蔽字恢复 */
	sigprocmask(SIG_SETMASK,&oldmask,NULL);

	return unslept;
}
