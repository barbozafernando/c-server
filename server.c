#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>

#include "http.h"

int main() {
  int s         = socket(AF_INET, SOCK_STREAM, 0);
  uint16_t PORT = htons(SERVER_PORT);

  struct sockaddr_in addr = {AF_INET, PORT, {0}, {0}};

  int b = bind(s, (const struct sockaddr*)&addr, sizeof(addr));
  if (b == -1) {
    perror("bind");
    exit(EXIT_FAILURE);
  }

  listen(s, MAX_QUEUED_REQUESTS);

  fprintf(stdout, "Listening on port: %d\n", SERVER_PORT);

  int client_fd       = {0};
  socklen_t addr_size = sizeof(addr);

  fprintf(stdout, "Waiting for connections...\n");
  client_fd = accept(s, (struct sockaddr*)&addr, &addr_size);
  fprintf(stdout, "Connected...\n");
  handle_http_request(client_fd);

  close(s);
  close(client_fd);

  return EXIT_SUCCESS;
}
