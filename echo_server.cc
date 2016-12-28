// TCP echo server.  Largely typed in from UNP 3e,
// apart from using my own function wrappers.

#include "exc_socket.h"
#include <string>
#include <iostream>
#include <cstring>
#include <unistd.h>
#include <sys/wait.h>

const int SERV_PORT = 4000;
const int MAXLINE = 4096;

void str_echo (socket_t sockfd) {
    ssize_t n;
    char buf[MAXLINE];

    while ( (n = recv (sockfd, buf, MAXLINE, 0)) > 0) {
        send(sockfd, buf, n, 0);
    }
}

int main(int argc, char** argv) {
    socket_t listenfd, connfd;
    socklen_t clilen;
    pid_t child_pid;
    struct sockaddr_in cliaddr, servaddr;
    int port = SERV_PORT;

    if (argc == 2)
        port = atoi (argv[1]);

    try {
        listenfd = Socket (AF_INET, SOCK_STREAM, 0);
        memset (&servaddr, 0, sizeof(servaddr));
        servaddr.sin_family = AF_INET;
        servaddr.sin_addr.s_addr = htonl (INADDR_ANY);
        servaddr.sin_port = htons (port);

        Bind (listenfd, (sockaddr *) &servaddr, sizeof(servaddr));
        Listen (listenfd, 20);

        while (true) {
            clilen = sizeof (cliaddr);
            connfd = Accept (listenfd, (sockaddr *) &cliaddr, &clilen);

            if ( (child_pid = Fork()) == 0) {
                if ( (child_pid = Fork()) == 0) {
                    Close (listenfd);
                    str_echo (connfd);
                    exit(0);
                } else 
                    exit(0);
            }
            Close (connfd);
            Waitpid(child_pid, nullptr, 0);
        }
    }
    catch (const std::exception& e) {
        Close (listenfd);
        Close (connfd);

        std::cout << "Exception: " << e.what() << "\n";
    }
}


