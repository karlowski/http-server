#include <stddef.h>
#include <unistd.h>
#include <string.h>
#include <sys/socket.h>
#include <pthread.h>
#include <stdio.h>

#include "../parser/parser.h"


void* router(void *connectionFd)
{
    char buffer[REQUEST_MAX_SIZE_BYTES];

    ssize_t bufferSize = read(*(int *)connectionFd, buffer, sizeof(buffer)); // buffer fills up here

    Request request = {0};

    parseRequest(&request, buffer, bufferSize);

    // TODO:
    // pthread_t threadId;
    // pthread_create(&threadId, NULL, parseRequest, &request);

    const char* response =
        "HTTP/1.1 200 OK\r\n"
        "Content-Type: text/plain\r\n"
        "Content-Length: 12\r\n"
        "\r\n"
        "Hello World!";

    write(*(int *)connectionFd, response, strlen(response));
    close(*(int *)connectionFd);

    return NULL;
}
