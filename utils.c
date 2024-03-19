#include <fcntl.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <string.h>

#include "utils.h"

const char *get_filename_from_request(char *buf) {
  char *f = buf + 5;
  *strchr(f, ' ') = 0;

  return f;
}

char *get_http_verb(char *request) {
  char *ptr_verb = calloc(6, sizeof(char) * 6);

  if (!ptr_verb) {
    perror("get_http_verb");
    exit(1);
  }

  for (size_t i = 0; request[i] != ' '; ++i) {
    ptr_verb[i] = request[i];
  }

  return ptr_verb;
}

char *read_file(const char *filename) {
  char *ptr_buf = calloc(65536, sizeof(char));
  int fd = open(filename, O_RDONLY);
  int bytes_read = read(fd, ptr_buf, 65536); // 64K

  if (bytes_read < 0) {
    perror("read_file");
    exit(EXIT_FAILURE);
  }

  return ptr_buf;
};

char *generate_response(char *contents, char* verb) {
  char *header = "HTTP/1.1 200 OK\r\nContent-Type: text/html; charset=utf-8\r\n\r\n";
  char *ptr_response = calloc(strlen(contents) + strlen(header), sizeof(char));

  strcat(ptr_response, header);
  strcat(ptr_response, contents);
  strcat(ptr_response, "\r\n");

  return ptr_response;
};

void send_response(int fd, char *response, int response_length) {
  int bytes_sent = send(fd, response, response_length, 0);

  if (bytes_sent < 0) {
    perror("send");
    exit(EXIT_FAILURE);
  }
}

void handle_http_request(int fd) {
  char request[REQUEST_BUFFER_SIZE];

  int bytes_recvd = recv(fd, request, REQUEST_BUFFER_SIZE - 1, 0);

  if (bytes_recvd < 0) {
    perror("recv");
    exit(EXIT_FAILURE);
  }

  char *verb = get_http_verb(request);
  char *file_content = {0};
  char *response = {0};
  const char *filename = {0};

  if (strcmp(verb, "GET") == 0) {
    filename = get_filename_from_request(request);
    file_content = read_file(filename);
    response = generate_response(file_content, "GET");

    send_response(fd, response, strlen(response));
  } else {
    perror("verb not implemented yet");
  }

  free(verb);
  free(file_content);
  free(response);
}
