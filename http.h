#ifndef _HTTP_H_
#define _HTTP_H_

#define SERVER_PORT          3000
#define REQUEST_BUFFER_SIZE  65536 // 64K
#define RESPONSE_BUFFER_SIZE 65536
#define MAX_QUEUED_REQUESTS  10
#define HTTP_HEADER          "HTTP/1.1 200 OK\r\n";

enum HTTP_STATUS_CODE {
  OK = 200,
  NOT_FOUND = 404,
};

void handle_http_request(int fd);
char *generate_response(char *contents, char* mime_type, char* verb);
char *get_http_verb(char *request, char *buf);
void send_response(int fd, char *response, int response_length);

#endif
