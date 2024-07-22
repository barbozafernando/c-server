#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <stdint.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <assert.h>

#include "file.h"
#include "http.h"
#include "mime.h"

#define HEADER_SIZE 1048576 // 1MB

void get_http_verb(char *request, char* verb) {
  size_t nbytes = strcspn(request, " ");
  assert(verb != NULL);
  strncpy((char*)verb, request, nbytes);
}

void generate_response(char *contents, char *mime_type, char *bres) {
  char header[HEADER_SIZE] = "HTTP/1.1 200 OK\r\nContent-Type:";
  strcat(header, mime_type);

  assert(bres != NULL);

  strcat(bres, header);
  strcat(bres, "\r\n\r\n");
  strcat(bres, contents);
};

void send_response(int fd, char *response, size_t response_length) {
  int bytes_sent = send(fd, response, response_length, 0);

  assert(response != NULL);

  if (bytes_sent == -1) {
    perror("send");
  }
}

void handle_http_request(int fd) {
  char *ptr_request = calloc(REQUEST_BUFFER_SIZE, sizeof(char));

  if (!ptr_request) {
    perror("handle_http_request");
  }

  int bytes_recvd = recv(fd, ptr_request, REQUEST_BUFFER_SIZE - 1, 0);

  if (bytes_recvd < 0) {
    perror("recv");
  }

  char verb[10] = {0};
  get_http_verb(ptr_request, &verb[0]);
  char *file_content_buf = calloc(FILE_MAX_SIZE, sizeof(char));

  if (!file_content_buf) {
    perror("handle_http_request");
  }

  char mime_type[25] = {0};
  size_t response_size = HEADER_SIZE + strlen(file_content_buf);
  char *response_buf = calloc(response_size, sizeof(char));
  if (!response_buf) {
    perror("error response_buf mallocing memory");
  }

  const char *filename_buf = calloc(FILENAME_MAX_SIZE, sizeof(char));
  if (!filename_buf) {
    perror("error filename_buf mallocing memory");
  }

  if (strcmp(verb, "GET") == 0) {
    get_filename_from_request(ptr_request, filename_buf);
    read_file(filename_buf, file_content_buf);
    get_mime_type(filename_buf, mime_type);
    generate_response(file_content_buf, mime_type, response_buf);

    send_response(fd, response_buf, strlen(response_buf));
  } else {
    perror("verb not implemented yet");
  }

  free(ptr_request);
  free(file_content_buf); 
  free(response_buf);
  free((void*)filename_buf); 
}
