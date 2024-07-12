#ifndef _HTTP_H_
#define _HTTP_H_

#include <stddef.h>

#define SERVER_PORT          3000
#define REQUEST_BUFFER_SIZE  65536 // 64K
#define RESPONSE_BUFFER_SIZE 65536
#define MAX_QUEUED_REQUESTS  10
#define HTTP_HEADER          "HTTP/1.1 200 OK\r\n";

typedef enum {
  OK = 200,
  NOT_FOUND = 404,
} HttpStatusCode;

void handle_http_request(int fd);
void generate_response(char *contents, char* mime_type, char* verb);
void get_http_verb(char *request, char *verb);
void send_response(int fd, char *response, size_t response_length);

#endif
