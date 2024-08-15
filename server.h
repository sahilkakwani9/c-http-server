#ifndef Server_h
#define Server_h

#include <netinet/in.h>
#include <sys/socket.h>


struct Server {
    int domain;
    int service;
    int protocol;
    int port;
    int backlog;
    u_long interface;
    struct sockaddr_in address;
    int socket;
    void (*launch)(struct Server *server);
};

struct Server server_constructor(int domain, int service, int protocol, int port, int backlog, u_long interface, void (*launch)(struct Server *server));

#endif