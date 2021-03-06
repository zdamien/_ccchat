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
    socket_t sock = Tcp_Connect (server, port);
    try {
        //chat sock, ...
    }
    catch (...) {
        Close (sock);
        throw;
    }
    close (sock);

}

void server (int port) {
    struct sockaddr_in cliaddr;

    socket_t listenfd = Tcp_Bind (port);
    try {
        while (true) {
            socklen_t clilen = sizeof (cliaddr);
            socket_t client_sock = Accept (listenfd, (sockaddr *) &cliaddr, &clilen);
            try {
            // chat
            }
            catch (...) {
                Close (client_sock);
                throw;
            }
            Close (client_sock);
        }
    }
    catch (...) {
        Close (listenfd);
        throw;
    }
    Close (listenfd);
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
