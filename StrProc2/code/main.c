#include <stdio.h>
#include <stdlib.h>

#include "strproc2.h"

int main() {
	char *str=GetString("this is %s library","string proccessing");
	STRING string;
	int i;
	
	printf("%s\n",str);
	
	string=Split(str,' ');
	
	printf("size: %d\n",string.size);
	for(i=0;i<string.size;i++){
		printf("%s\n",string.strings[i]);
	}
	
	DeleteString(&string);
	free(str);
	printf("end program\n");
	
	return 0;
}
