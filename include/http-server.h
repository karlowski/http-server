#include "http-server.types.h"

HttpServerConfig createHttpServerConfig(int port);
int createHttpServer(HttpServerConfig* config);
int runHttpServer(HttpServerConfig* config);
int shutdownHttpServer(HttpServerConfig* config);
