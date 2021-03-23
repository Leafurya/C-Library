#include <stdio.h>
#include <stdlib.h>
#include "Socket.h"
#include <string.h>

/* run this program using the console pauser or add your own getch, system("pause") or input loop */

int main() {
	SOCKET sock;
	SOCKET client;
	char *data="send data";
	
	printf("result: %d\n",CreateServer(&sock,"2020"));
	client=AcceptClient(sock);
	Send(client,data,strlen(data)+1);
	
	
	getchar();
	
	return 0;
}
