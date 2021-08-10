#include<string.h>
#include<limits.h>

#define MAXSTRINGSZ 4096

/*
 * 注意，这个函数实现不是线程安全的，因为调用此函数
 * 的返回值都指向同一块静态内存
 */
static char envbuf[MAXSTRINGSZ];

extern char **environ;

char *mygetenv(const char *name){
	int len = strlen(name);

	for(int i=0;environ[i]!=NULL;i++){
		if((strncmp(name,environ[i],len)==0)&&(environ[i][len]=='=')){
			strncpy(envbuf,environ[i][len+1],MAXSTRINGSZ-1);
			return envbuf;
		}
	}

	return NULL;
}
