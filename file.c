#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

#include "file.h"

const char *get_filename_from_request(char *buf) {
  char *f = buf + 5;
  *strchr(f, ' ') = 0;

  return f;
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
