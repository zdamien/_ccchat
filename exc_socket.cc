#include "exc_socket.h"
#include <system_error>

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
    int retval = close (socket);
    if (retval < 0)
        throw std::system_error(errno, std::system_category());
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
