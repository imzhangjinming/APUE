#include<stdio.h>

int main(void){
	int a = 0x04030201;

	if(*(char*)(&a)==0x01)
		printf("little endian\n");
	else if(*(char*)(&a)==0x04)
		printf("big endian\n");
	else
		printf("can't determine\n");
}
