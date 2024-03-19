#ifndef _UTILS_H_
#define _UTILS_H_

#define SERVER_PORT          3000
#define REQUEST_BUFFER_SIZE  65536 // 64K
#define RESPONSE_BUFFER_SIZE 65536
#define MAX_QUEUED_REQUESTS  10
#define HTTP_HEADER          "HTTP/1.1 200 OK\r\n";

enum HTTP_STATUS_CODE {
  OK = 200,
  NOT_FOUND = 404,
};

const char *get_filename_from_request(char *buf);
void handle_http_request(int fd);
char *read_file(const char *filename);
char *generate_response(char *contents, char* verb);
void handle_http_request(int fd);

#endif
