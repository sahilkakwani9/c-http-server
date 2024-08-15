#include "server.h"
#include <stdio.h>
#include <string.h>
#include <unistd.h>

void launch(struct Server *server)
{

    char buffer[30000];

    int server_addr_length = sizeof(server->address);
    int new_socket;

    while (1)
    {
        printf("==== Waiting For Connnection ====");
        new_socket = accept(server->socket, (struct sockaddr *)&server->address, (socklen_t *)&server_addr_length);
        read(new_socket, buffer, 30000);
        printf("%s\n", buffer);
        char *response = "HTTP/1.1 200 OK\r\n"
                         "Date: Fri, 16 Aug 2024 12:00:00 GMT\r\n"
                         "Server: Apache/2.4.41 (Unix)\r\n"
                         "Content-Type: text/html; charset=UTF-8\r\n"
                         "Content-Length: 184\r\n"
                         "Connection: close\r\n"
                         "\r\n"
                         "<!DOCTYPE html>\r\n"
                         "<html>\r\n"
                         "<head>\r\n"
                         "    <title>Welcome to my HTTP server</title>\r\n"
                         "</head>\r\n"
                         "<body>\r\n"
                         "    <h1>Welcome to my HTTP server</h1>\r\n"
                         "    <p>I fucki'n wrote this in c</p>\r\n"
                         "</body>\r\n"
                         "</html>\r\n";
        ;
        write(new_socket, response, strlen(response));
        close(new_socket);
    }
}

int main()
{
    struct Server server = server_constructor(AF_INET, SOCK_STREAM, 0, 3000, 10, INADDR_ANY, launch);
    server.launch(&server);
}