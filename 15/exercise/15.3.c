#include<stdio.h>
#include<stdlib.h>

int main(void){
	FILE *fp = popen("meaninglesscmd","r");

	if(fp==NULL)
		printf("popen return a null pointer\n");
	else
		printf("popen return a non-null pointer\n");

	exit(0);
}

