#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <string.h>
#include <fcntl.h>
#include <sys/sendfile.h>
#include <unistd.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define RESPONSE_BUFFER_LENGTH 256

const char* get_filename_from_response(char* buf) {
  char* f = buf + 5;
  *strchr(f, ' ') = 0;

  return f;
}

int main() {
  int s = socket(AF_INET, SOCK_STREAM, 0);
  uint16_t PORT = htons(8080);

  struct sockaddr_in addr = {
    AF_INET,
    PORT,
    {0}
  };

  bind(s, (const struct sockaddr*)&addr, sizeof(addr));
  listen(s, 10);
  
  int client_fd = accept(s, 0, 0);

  char response_buffer[RESPONSE_BUFFER_LENGTH] = {0};
  recv(client_fd, response_buffer, RESPONSE_BUFFER_LENGTH, 0);

  const char* filename = get_filename_from_response(response_buffer);
  int fd = open(filename, O_RDONLY);
  sendfile(client_fd, fd, 0, RESPONSE_BUFFER_LENGTH);

  close(fd);
  close(client_fd);
  close(atoi(filename));

  return 0;
}