#include <arpa/inet.h>
#include <fcntl.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/sendfile.h>
#include <sys/socket.h>
#include <unistd.h>

#include "http.h"

int main() {
  int s = socket(AF_INET, SOCK_STREAM, 0);
  uint16_t PORT = htons(SERVER_PORT);

  struct sockaddr_in addr = {AF_INET, PORT, {0}};

  bind(s, (const struct sockaddr *)&addr, sizeof(addr));
  listen(s, MAX_QUEUED_REQUESTS);

  fprintf(stdout, "Listening on port: %d\n", SERVER_PORT);

  int client_fd = accept(s, 0, 0);

  handle_http_request(client_fd);

  close(s);
  close(client_fd);

  return EXIT_SUCCESS;
}
