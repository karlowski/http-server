#include <stddef.h>


#define REQUEST_MAX_SIZE_BYTES 8192


typedef struct {
    char* key;
    char* value;
} HeaderItem;

typedef struct {
    HeaderItem* data;
    size_t size;
} HttpHeaders;

typedef struct {
    char* data;
    char* contentType;
} HttpBody;

typedef struct {
    char* method;
    char* url;
    char* protocol;
    HttpHeaders* headers;
    HttpBody* body;
} Request;

void parseToken(char buffer[REQUEST_MAX_SIZE_BYTES], size_t size, int* scanner, char** token);
void parseRequest(Request* r, char buffer[REQUEST_MAX_SIZE_BYTES], size_t bufferSize);
void freeRequest(Request* r);
