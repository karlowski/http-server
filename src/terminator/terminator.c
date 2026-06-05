#define _XOPEN_SOURCE 700

#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <sys/socket.h>

#include "../include/http-server.types.h"

HttpServerConfig* globalServerConfig;

void onSigint(int)
{
    (*globalServerConfig).active = 0;
}

void registerSigintHandler(HttpServerConfig* config)
{
    globalServerConfig = config;

    struct sigaction sa = {
        .sa_handler = onSigint,
        .sa_flags = 0
    };

    sigemptyset(&sa.sa_mask);
    sigaction(SIGINT, &sa, NULL);
}
