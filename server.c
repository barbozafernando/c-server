#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

#include "http.h"

int main() {
  int sockfd = socket(AF_INET, SOCK_STREAM, 0);
  uint16_t PORT = htons(SERVER_PORT);

  struct sockaddr_in addr = {AF_INET, PORT, {0}, {0}};

  int b = bind(sockfd, (const struct sockaddr *)&addr, sizeof(addr));
  if (b == -1) {
    perror("bind");
    close(sockfd);
    exit(EXIT_FAILURE);
  }

  listen(sockfd, MAX_QUEUED_REQUESTS);

  fprintf(stdout, "Listening on port: %d\n", SERVER_PORT);

  int client_fd = {0};
  socklen_t addr_size = sizeof(addr);

  fprintf(stdout, "Waiting for connections...\n");
  client_fd = accept(sockfd, (struct sockaddr *)&addr, &addr_size);
  fprintf(stdout, "Connected...\n");
  handle_http_request(client_fd);

  close(client_fd);
  close(sockfd);

  return EXIT_SUCCESS;
}
