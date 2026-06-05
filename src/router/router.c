#include <stddef.h>
#include <unistd.h>
#include <string.h>
#include <sys/socket.h>

#define REQUEST_SIZE_BYTES 4096

void* router(void* connectionFd)
{
    char buffer[REQUEST_SIZE_BYTES];

    read(*(int*)connectionFd, buffer, sizeof(buffer));

    const char *response =
        "HTTP/1.1 200 OK\r\n"
        "Content-Type: text/plain\r\n"
        "Content-Length: 12\r\n"
        "\r\n"
        "Hello World!";

    write(*(int*)connectionFd, response, strlen(response));
    close(*(int*)connectionFd);

    return NULL;
}
