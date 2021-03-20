#ifndef _socketserver__h_
#define _socketserver__h_

#ifdef __cplusplus
extern "C"{
#endif

#include <winsock2.h>


int CreateServer(SOCKET *sock,char *port);
void DisconnectClient(SOCKET client);
SOCKET AcceptClient(SOCKET server);
void DestroyServer(SOCKET sock);

#ifdef __cplusplus
}
#endif
#endif
