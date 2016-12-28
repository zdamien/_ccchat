#include "exc_socket.h"
#include <string>
#include <cstdio>
using std::string;

const string help_string = R"(Usage:
        ccchat server <port number>
        ccchat client <host name or IP> <port number>
        )";

void client (string server, int port) {
}

void server (int port) {
}

int main(int argc, char** argv) {
    try {
        if (argc == 3 && argv[1] == "client") {
            int port = atoi (argv[3]);
            client (argv[2], port);
        }
        else if (argc == 2 && argv[1] == "server") {
            int port = atoi (argv[3]);
            server (port);
        }
        else
            printf ("Invalid arguments.\n%s\n", help_string.c_str());

    }
    catch (...) {
    }
}
