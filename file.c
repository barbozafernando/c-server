#include <fcntl.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

#include "file.h"

const char *get_filename_from_request(char *request) {
  const char* DEFAULT_FILENAME = "index.html";
  const char *filename = {0};
  size_t offset = 5;

  char *s = request + offset;

  if (s[0] == 32) {
    return DEFAULT_FILENAME;
  }

  size_t nbytes = strcspn(s, " ");
  strncpy((char *)filename, request, nbytes);

  return filename;
}

char *read_file(const char *filename) {
  char *ptr_buf = calloc(FILE_MAX_SIZE, sizeof(char));

  if (!ptr_buf) {
    perror("read_file");
    exit(EXIT_FAILURE);
  }

  int fd = open(filename, O_RDONLY);
  if (fd == -1) {
    perror("file not found");
  }

  int bytes_read = read(fd, ptr_buf, FILE_MAX_SIZE);

  if (bytes_read < 0) {
    perror("read_file");
    exit(EXIT_FAILURE);
  }

  fprintf(stdout, "%d bytes read.\n", bytes_read);
  return ptr_buf;
};
