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
  char *ptr_buf = calloc(65536, sizeof(char));
  int fd = open(filename, O_RDONLY);
  int bytes_read = read(fd, ptr_buf, 65536); // 64K

  if (bytes_read < 0) {
    perror("read_file");
    exit(EXIT_FAILURE);
  }

  return ptr_buf;
};
