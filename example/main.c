#include <arpa/inet.h>
#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>

#include "../include/http-server.h"

int main()
{
    HttpServerConfig config = createHttpServerConfig(8080);

    createHttpServer(&config);
    runHttpServer(&config);

    return 0;
}
