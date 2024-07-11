#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <stdint.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

#include "file.h"
#include "http.h"
#include "mime.h"

#define HEADER_SIZE 1024

void get_http_verb(char *request, char* verb) {
  size_t nbytes = strcspn(request, " ");
  strncpy((char*)verb, request, nbytes);
}

char *generate_response(char *contents, char *mime_type, char *verb) {
  char header[HEADER_SIZE] = "HTTP/1.1 200 OK\r\nContent-Type:";
  strcat(header, mime_type);
  size_t response_size = strlen(contents) + strlen(header);
  char *ptr_response = calloc(response_size, sizeof(char));

  if (!ptr_response) {
    perror("generate_response");
    exit(EXIT_FAILURE);
  }

  strcat(ptr_response, header);
  strcat(ptr_response, "\r\n\r\n");
  strcat(ptr_response, contents);

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
  char *ptr_request = calloc(REQUEST_BUFFER_SIZE, sizeof(char));

  if (!ptr_request) {
    perror("handle_http_request");
    exit(EXIT_FAILURE);
  }

  int bytes_recvd = recv(fd, ptr_request, REQUEST_BUFFER_SIZE - 1, 0);

  if (bytes_recvd < 0) {
    perror("recv");
    exit(EXIT_FAILURE);
  }

  char verb[10] = {0};
  get_http_verb(ptr_request, &verb[0]);
  char *file_content = calloc(FILE_MAX_SIZE, sizeof(char));

  if (!file_content) {
    perror("handle_http_request");
    exit(EXIT_FAILURE);
  }

  char *response = {0};
  char mime_type[25] = {0};
  const char *filename = {0};

  if (strcmp(verb, "GET") == 0) {
    filename = get_filename_from_request(ptr_request);
    file_content = read_file(filename);
    get_mime_type(filename, mime_type);
    response = generate_response(file_content, mime_type, "GET");

    send_response(fd, response, strlen(response));
  } else {
    perror("verb not implemented yet");
  }

  /* free(response); */
  /* free(ptr_request); */
  /* free(file_content); */
}
