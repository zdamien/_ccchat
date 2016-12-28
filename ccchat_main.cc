#include "exc_socket.h"
#include <string>
#include <cstdio>
#include <iostream>
#include <string.h>
using std::string;
using std::cout;

const string help_string = R"(Usage:
        ccchat server <port number>
        ccchat client <host name or IP> <port number>
)";

void client (char* server, int port) {
    struct sockaddr_in servaddr;
    memset (&servaddr, 0, sizeof(servaddr));

    socket_t sock = Socket ( AF_INET, SOCK_STREAM, 0);
    try {
        servaddr.sin_family = AF_INET;
        servaddr.sin_port = port;
        Inet_pton(AF_INET, server, &servaddr.sin_addr);

        Connect (sock, (sockaddr *) &servaddr, sizeof(servaddr));

        //chat sock, ...
    }
    catch (...) {
        Close (sock);
        throw;
    }
    close (sock);

}

void server (int port) {
    struct sockaddr_in servaddr, cliaddr;
    memset (&servaddr, 0, sizeof(servaddr));

    socket_t listenfd = Socket ( AF_INET, SOCK_STREAM, 0);
    socket_t client_sock;
    try {
        servaddr.sin_family = AF_INET;
        servaddr.sin_addr.s_addr = htonl (INADDR_ANY);
        servaddr.sin_port = htons (port);

        Bind (listenfd, (sockaddr *) &servaddr, sizeof(servaddr));
        Listen (listenfd, 20);

        while (true) {
            unsigned int clilen = sizeof (cliaddr);
            client_sock = Accept (listenfd, (sockaddr *) &cliaddr, &clilen);
            // chat
            Close (client_sock);
        }
    }
    catch (...) {
        Close (listenfd);
        Close (client_sock);
        throw;
    }
    Close (listenfd);
    Close (client_sock);
}

int main(int argc, char** argv) {
    try {
        if (argc == 4 && string(argv[1]) == "client") {
            int port = atoi (argv[3]);
            client (argv[2], port);
        }
        else if (argc == 3 && string(argv[1]) == "server") {
            int port = atoi (argv[2]);
            server (port);
        }
        else
            cout << "Invalid arguments\n" << help_string;

    }
    catch (const std::exception& e) {
        std::cout << "Exception: " << e.what() << "\n";
    }
}
