#include "socket_server.h"

int CreateServer(SOCKET *sock,char *port){
	WSADATA wsaData;
	struct sockaddr_in addrServer;
	int sendSize;
	int i=0,j;
	u_long sock_on=1;
	int error;
	
	WSAStartup(MAKEWORD(2,2),&wsaData);
	
	*sock=socket(PF_INET,SOCK_STREAM,0);
	
	memset(&addrServer,0,sizeof(addrServer));
	addrServer.sin_family=AF_INET;
	addrServer.sin_addr.s_addr=htonl(INADDR_ANY);
	addrServer.sin_port=htons(atoi(port));
	
	error=-1;
	if(bind(*sock,(SOCKADDR *)&addrServer,sizeof(addrServer))){
		error=GetLastError();
		return error;
	}
	
	listen(*sock,5);
	return error;
}
void DisconnectClient(SOCKET client){
	closesocket(client);
}

SOCKET AcceptClient(SOCKET server){
	SOCKET client;
	struct sockaddr_in addrClient;
	int clientSize;
	
	clientSize=sizeof(addrClient);
	
	client=accept(server,(SOCKADDR *)&addrClient,&clientSize);
	
	return client;
}
void DestroyServer(SOCKET sock){
	closesocket(sock);
	WSACleanup();
}

