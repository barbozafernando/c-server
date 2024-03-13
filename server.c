#include <arpa/inet.h>
#include <fcntl.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/sendfile.h>
#include <sys/socket.h>
#include <unistd.h>

#define SERVER_PORT 8080
#define REQUEST_BUFFER_LENGTH 1024
#define RESPONSE_BUFFER_LENGTH 1024
#define MAX_QUEUED_REQUESTS 10

const char *get_filename_from_response(char *buf) {
  char *f = buf + 5;
  *strchr(f, ' ') = 0;

  return f;
}

int main() {
  int s = socket(AF_INET, SOCK_STREAM, 0);
  uint16_t PORT = htons(SERVER_PORT);

  struct sockaddr_in addr = {AF_INET, PORT, {0}};

  (void)bind(s, (const struct sockaddr *)&addr, sizeof(addr));
  listen(s, MAX_QUEUED_REQUESTS);

  fprintf(stdout, "Listening on port: %d\n", SERVER_PORT);

  int client_fd = accept(s, 0, 0);

  char request_buffer[REQUEST_BUFFER_LENGTH] = {0};
  char response_buffer[RESPONSE_BUFFER_LENGTH] = {0};
  char http_header[4096] = "HTTP/1.1 200 OK\r\n\r\n";

  recv(client_fd, request_buffer, REQUEST_BUFFER_LENGTH, 0);

  const char *filename = get_filename_from_response(request_buffer);
  int fd = open(filename, O_RDONLY);
  int fd2 = read(fd, response_buffer, RESPONSE_BUFFER_LENGTH);
  strcat(http_header, response_buffer);
  strcat(http_header, "\r\n\r\n");
  strcpy(response_buffer, http_header);
  send(client_fd, response_buffer, RESPONSE_BUFFER_LENGTH, 0);

  printf("response:%s\n", response_buffer);

  close(s);
  close(fd);
  close(fd2);
  close(client_fd);

  return EXIT_SUCCESS;
}
