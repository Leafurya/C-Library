#include <stdio.h>
#include <stdlib.h>
#include "Socket.h"

/* run this program using the console pauser or add your own getch, system("pause") or input loop */

int main() {
	SOCKET sock;
	CommSize size;
	char *data;
	
	printf("result: %d\n",ConnectServer(&sock,"127.0.0.1","2020"));
	data=Recv(sock,&size);
	printf("size: %d\ndata:%s\n",size,data);
	
	getchar();
	return 0;
}
