#include <signal.h>

#ifndef HTTP_SERVER_TYPES_H
#define HTTP_SERVER_TYPES_H

typedef int serverFd;
typedef volatile sig_atomic_t status;
typedef struct {
    serverFd fd;
    int port;
    status active;
} HttpServerConfig;

#endif
