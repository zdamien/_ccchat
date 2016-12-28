#include "exc_socket.h"
#include <system_error>
#include <string.h>

socket_t Socket(int domain, int type, int protocol) {
    int retval = socket(domain, type, protocol);
    if (retval > 0)
        return socket_t{retval};
    else 
        throw std::system_error(errno, std::system_category());
}

void Bind(socket_t socket, const struct sockaddr *address, socklen_t
        address_len) {
    int retval = bind(socket, address, address_len);
    printf("bind %d %d %d\n",socket, retval, errno);
    if (retval < 0)
        throw std::system_error(errno, std::system_category());
}

void Listen(socket_t socket, int backlog) {
    int retval = listen(socket, backlog);
    if (retval < 0)
        throw std::system_error(errno, std::system_category());
}

//socket_t Accept(socket_t socket, struct sockaddr *restrict address, socklen_t
//        *restrict address_len) {
// g++/clang specific restrict keyword
socket_t Accept(socket_t socket, struct sockaddr *__restrict__  address, socklen_t
        *__restrict__  address_len) {
    int retval = accept(socket, address, address_len);
    if (retval > 0)
        return socket_t{retval};
    else 
        throw std::system_error(errno, std::system_category());
}

void Connect(socket_t socket, const struct sockaddr *address, socklen_t
        address_len) {
    int retval = connect(socket, address, address_len);
    if (retval < 0)
        throw std::system_error(errno, std::system_category());
}

void Close (socket_t socket) {
    int retval;
loop: 
    retval = close (socket);
    if (retval < 0) {
        if (EINTR == errno) // interrupted, try again
            goto loop;
    }
     //   throw std::system_error(errno, std::system_category());
}

pid_t Fork() {
    int retval = fork();
    if (retval < 0)
        throw std::system_error(errno, std::system_category());
    else
        return retval;
}

pid_t Waitpid(pid_t pid, int *stat_loc, int options) {
    int retval = waitpid (pid, stat_loc, options);
    if (retval < 0)
        throw std::system_error(errno, std::system_category());
    else
        return retval;
}

void Inet_pton(int af, const char *src, void *dst) {
    int retval = inet_pton (af, src, dst);
    if (retval == 0) 
        throw std::runtime_error("Inet_pton: invalid network address");
    if (retval == -1)
        throw std::logic_error("Inet_pton: invalid address family");
}

#include <cstdio>

socket_t Tcp_Bind ( int port, int listeners) {

    socket_t listenfd = Socket ( AF_INET, SOCK_STREAM, 0);

    sockaddr_in servaddr;
    socklen_t address_len = sizeof(servaddr);

    memset (&servaddr, 0, address_len);
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = htonl (INADDR_ANY);
    servaddr.sin_port = htons (port);

    try {
        printf("t1 %d\n",listenfd);
        Bind (listenfd, (sockaddr *) &servaddr, address_len);
        printf("t2\n");
        Listen (listenfd, listeners);
        printf("t3\n");
    }
    catch (...) {
        printf("te1\n");

        Close (listenfd);
        printf("te2\n");
        throw;
    }

    return listenfd;

}

socket_t Tcp_Connect ( string address_s, int port) {
    socket_t connfd = Socket (AF_INET, SOCK_STREAM, 0);

    sockaddr_in servaddr; 
    socklen_t address_len = sizeof (servaddr);

    memset (&servaddr, 0, address_len);
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons (port);
    Inet_pton (AF_INET, address_s.c_str(), &servaddr.sin_addr);

    try {
        Connect (connfd, (sockaddr *) &servaddr, address_len);
    }
    catch (...) {
        Close (connfd);
        throw;
    }
    return connfd;
}
