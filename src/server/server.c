#include <stdio.h>
#include <sys/socket.h>
#include <bits/socket.h>
#include <arpa/inet.h>
#include <pthread.h>
#include <unistd.h>
#include <signal.h>

#include "../include/http-server.h"
#include "../router/router.h"
#include "../terminator/terminator.h"

serverFd initializeSocket(int port)
{
    int serverFd = socket(AF_INET, SOCK_STREAM, 0);
    struct sockaddr_in address = {
        .sin_family = AF_INET,
        .sin_port = htons(port),
        .sin_addr.s_addr = INADDR_ANY};

    int opt = 1;
    setsockopt(serverFd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));
        
    int isBound = bind(serverFd, (struct sockaddr *)&address, sizeof(address));

    if (serverFd < 0 || isBound < 0)
    {
        perror("bind");
        return -1;
    }

    return serverFd;
}

HttpServerConfig createHttpServerConfig(int port)
{
    return (HttpServerConfig) {
        .fd = 0,
        .port = port,
        .active = 0
    };
}

int createHttpServer(HttpServerConfig* config)
{
    serverFd fd = initializeSocket((*config).port);

    if (fd < 0)
    {
        return -1;
    }

    (*config).fd = fd;

    return 0;
}

int runHttpServer(HttpServerConfig *config)
{
    int isListening = listen((*config).fd, 10);

    if (isListening < 0)
    {
        return -1;
    }

    registerSigintHandler(config);
    (*config).active = 1;

    printf("http server is listening on port: %d\n", (*config).port);

    while ((*config).active > 0)
    {
        int connection = accept((*config).fd, NULL, NULL);

        if (connection < 0)
        {
            continue;
        }

        pthread_t threadId;
        pthread_create(&threadId, NULL, router, &connection);
    }

    shutdownHttpServer(config);
    return 0;
}

int shutdownHttpServer(HttpServerConfig *config)
{
    if ((*config).active > 0)
    {
        (*config).active = 0;
    }

    shutdown((*config).fd, SHUT_RDWR);
    close((*config).fd);
    
    printf("http server was shut down successfully\n");

    return 0;
}
