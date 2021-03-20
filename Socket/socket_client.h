#ifndef _socketclient__h_
#define _socketclient__h_

#ifdef __cplusplus
extern "C"{
#endif

#include <winsock2.h>

int ConnectServer(SOCKET *sock,char *ip,char *port);
void DisconnectServer(SOCKET sock);

#ifdef __cplusplus
}
#endif
#endif
