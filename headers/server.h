#include <sys/socket.h>
#include <netinet/in.h>
#ifndef SERVER_H
#define SERVER_H

#define SERVER_PORT 8080
#define SERVER_ADDR "127.0.0.1"

typedef struct
{
    int server_fd;
    struct sockaddr_in address;
}server_config_struct;


server_config_struct setup_server();

#endif // SERVER_H