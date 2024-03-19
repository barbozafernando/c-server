#include <arpa/inet.h>
#include <fcntl.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/sendfile.h>
#include <sys/socket.h>
#include <unistd.h>

#include "utils.h"

int main() {
  int s = socket(AF_INET, SOCK_STREAM, 0);
  uint16_t PORT = htons(SERVER_PORT);

  struct sockaddr_in addr = {AF_INET, PORT, {0}};

  bind(s, (const struct sockaddr *)&addr, sizeof(addr));
  listen(s, MAX_QUEUED_REQUESTS);

  fprintf(stdout, "Listening on port: %d\n", SERVER_PORT);

  int client_fd = accept(s, 0, 0);

  handle_http_request(client_fd);

  /*
  recv(client_fd, request_buffer, REQUEST_BUFFER_SIZE, 0);

  const char *filename = get_filename_from_response(request_buffer);
  int fd = open(filename, O_RDONLY);
  int fd2 = read(fd, response_buffer, RESPONSE_BUFFER_SIZE);
  strcat(http_header, response_buffer);
  strcat(http_header, "\r\n\r\n");
  send(client_fd, http_header, strlen(http_header), 0);

  close(fd);
  close(fd2);
  */

  close(s);
  close(client_fd);

  return EXIT_SUCCESS;
}
