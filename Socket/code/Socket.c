#include "Socket.h"

//Server
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

//Client
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

//Communication
char *Recv(SOCKET sock,CommSize *pSize){
	char *data=0;
	int recvSize=0;
	CommSize size;
	int recvResult;
	
	recvResult=recv(sock,(char *)&size,sizeof(CommSize),0);
	switch(recvResult){
		case -1:
			data=0;
			break;
		case 0:
			data=0;
			break;
		default:
			data=(char *)malloc(sizeof(char)*size);
			while(1){
				recvResult=recv(sock,data+recvSize,size-recvSize,0);
				//printf("recvResult: %d\n",recvResult);
				recvSize+=recvResult;
				//printf("recvSize: %d\n",recvSize);
				if(recvSize>=size){
					break;
				}
			}
			break;
	}
	*pSize=size;
	//printf("recv done\n");
	return data;
}
char Send(SOCKET sock,void *data,int size){
	int sendSize=0;
	CommSize tsize=size;
	
	send(sock,(char *)&tsize,sizeof(tsize),0);
	while(1){
		sendSize=send(sock,(char *)(data+sendSize),size-sendSize,0);
		if(sendSize==-1){
			return 0;
		}
		else if(sendSize==size){
			return 1;
		}
	}
}
