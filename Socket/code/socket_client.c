#include "socket_client.h"

int ConnectServer(SOCKET *sock,char *ip,char *port){
	WSADATA wsaData;
	SOCKADDR_IN addrServer;
	int clientSize;
	int error=-1;
	
	WSAStartup(MAKEWORD(2,2),&wsaData);
	
	*sock=socket(PF_INET,SOCK_STREAM,0);
	
	memset(&addrServer,0,sizeof(addrServer));
	addrServer.sin_family=AF_INET;
	addrServer.sin_addr.s_addr=inet_addr(ip);
	addrServer.sin_port=htons(atoi(port));
	
	if(connect(*sock,(SOCKADDR *)&addrServer,sizeof(addrServer))==-1){
		error=GetLastError();
		DisconnectServer(*sock);
	}
	return error;
}
void DisconnectServer(SOCKET sock){
	closesocket(sock);
	WSACleanup();
}

