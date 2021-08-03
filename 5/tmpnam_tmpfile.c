#include"apue.h"

int main(void){
	char name[L_tmpnam],line[MAXLINE];
	FILE *fp;

	fprintf(stdout,"first tmpnam: %s\n",tmpnam(NULL));

	tmpnam(name);
	fprintf(stdout,"second tmpnam: %s\n",name);

	if((fp=tmpfile())==NULL)
		err_sys("error fmpfile");

	fputs("Hello world.First line.",fp);
	rewind(fp);

	if(fgets(line,sizeof(line),fp)==NULL)
		err_sys("error fgets");

	fputs(line,stdout);

	exit(0);
}	
