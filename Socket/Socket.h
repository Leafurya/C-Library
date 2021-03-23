#ifndef _socket__h_
#define _socket__h_

#ifdef __cplusplus
extern "C"{
#endif

#include <winsock.h>

typedef int CommSize;

//Server
int CreateServer(SOCKET *sock,char *port);
void DisconnectClient(SOCKET client);
SOCKET AcceptClient(SOCKET server);
void DestroyServer(SOCKET sock);

//Client
int ConnectServer(SOCKET *sock,char *ip,char *port);
void DisconnectServer(SOCKET sock);

//Communication
char *Recv(SOCKET sock,CommSize *pSize);
char Send(SOCKET sock,void *data,int size);

#ifdef __cplusplus
}
#endif
#endif
