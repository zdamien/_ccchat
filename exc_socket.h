// Exception-throwing wrappers to socket functions, capitalized a la Unix Network
// Programming.

#ifndef CCCHAT_EXC_SOCKET_H
#define CCCHAT_EXC_SOCKET_H

#include <sys/socket.h>

typedef int socket_t;  //might wrap file descriptors in a handle later

socket_t Socket(int domain, int type, int protocol);

void Bind(socket_t socket, const struct sockaddr *address, socklen_t address_len);

void Listen(socket_t socket, int backlog);

//socket_t Accept(socket_t socket, struct sockaddr *restrict address, socklen_t *restrict address_len);
socket_t Accept(socket_t socket, struct sockaddr *address, socklen_t *address_len);

void Connect(socket_t socket, const struct sockaddr *address, socklen_t address_len);

#endif
