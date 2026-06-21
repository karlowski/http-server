#include <stdlib.h>
#include <stdio.h>

#include "parser.h"


int isDelimiter(char symbol)
{
    return 
        symbol == ' ' || 
        symbol == '\r' || 
        symbol == '\n';
}

void parseToken(char buffer[REQUEST_MAX_SIZE_BYTES], size_t size, int* scanner, char** token)
{
    int length = 0;
    char delimiter;

    for (size_t i = *scanner; i < size; i++)
    {
        if (isDelimiter(buffer[i]))
        {
            delimiter = buffer[i];
            break;
        }

        length++;
    }

    *token = malloc(length + 1);
    int i = 0;
    for (int offset = *scanner; offset < *scanner + length; offset++)
    {
        (*token)[i] = buffer[offset];
        i++;
    }

    (*token)[length] = '\0';
    *scanner += length;

    if (delimiter == ' ') // TODO: this is really ugly
    {
        *scanner += + 1;
    } else 
    {
        *scanner += + 2;
    }
}

void parseRequest(Request* r, char buffer[REQUEST_MAX_SIZE_BYTES], size_t bufferSize)
{
    int scanner = 0;

    parseToken(buffer, bufferSize, &scanner, &r->method);
    parseToken(buffer, bufferSize, &scanner, &r->url);
    parseToken(buffer, bufferSize, &scanner, &r->protocol);

    // TODO: parse headers
    // TODO: rearrange body
}

void freeRequest(Request* r)
{
    free(r->method);
    free(r->url);
    free(r->protocol);
    free(r->headers);
    free(r->body);
}
