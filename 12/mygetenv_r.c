#include<string.h>
#include<limits.h>
#include<pthread.h>

extern char **environ;

pthread_mutex_t env_mutex;

static pthread_once_t init_done = PTHREAD_ONCE_INIT;

static void thread_init(void){
	pthread_mutexattr_t attr;

	pthread_mutexattr_init(&attr);
	pthread_mutexattr_settype(&attr,PTHREAD_MUTEX_RECURSIVE);
	pthread_mutex_init(&env_mutex,&attr);
	pthread_mytexattr_destroy(&attr);
}

int mygetenv_r(const char *name,char *buf,int buflen){
	int len,oldlen;

	pthread_once(&init_done,thread_init);
	len=strlen(name);
	pthread_mutex_lock(&env_mutex);
	for(int i=0;environ[i]!=NULL;i++){
		if((strncmp(name,environ[i],len)==0)&&(environ[i][len]=='=')){
			oldlen = strlen(&environ[i][len+1]);
			if(oldlen >= buflen){
				pthread_mutex_unlock(&env_mutex);
				return (ENOSPC);
			}
			strncpy(buf,&environ[i][len+1],oldlen);
			buf[oldlen]='\0';
			pthread_mutex_unlock(&env_mutex);
			return (0);
		}
	}

	pthread_mutex_unlock(&env_mutex);
	return (ENOENT);
}
	
