#include <stdio.h>
#include <fcntl.h>
#include <stdint.h>
#include <string.h>
#include <unistd.h>
#include <assert.h>

#include <sys/stat.h>
#include <sys/types.h>

#include "file.h"

void get_filename_from_request(char* request, const char* bfilename) {
  const char* DEFAULT_FILENAME = "pages/index.html";
  size_t offset = 5;

  assert(bfilename != NULL);

  char* s = request + offset;

  if (s[0] == 32) {
    strncpy((char*)bfilename, DEFAULT_FILENAME, strlen(DEFAULT_FILENAME));
  }

  size_t nbytes = strcspn(s, " ");
  strncpy((char*)bfilename, s, nbytes);
}

void read_file(const char* filename, char* bfile_content) {
  const char filename_not_found[] = "pages/404.html";

  assert(bfile_content != NULL);

  int fd = open(filename, O_RDONLY);
  if (fd == -1) {
    int fd = open(filename_not_found, O_RDONLY);
    int bytes_read = read(fd, bfile_content, FILE_MAX_SIZE / 2);
    if (bytes_read < 0) {
      perror("read_file_404");
    }
  }

  int bytes_read = read(fd, bfile_content, FILE_MAX_SIZE);

  if (bytes_read < 0) {
    perror("read_file");
  }

  fprintf(stdout, "%d bytes read.\n", bytes_read);
};
