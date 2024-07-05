#include <ctype.h>
#include <string.h>

#include "mime.h"

char *strlower(char *s) {
  for (char *p = s; *p != '\0'; p++) {
    *p = tolower(*p);
  }

  return s;
}

void get_mime_type(const char *filename, char buf[]) {
  char *ext = strrchr(filename, '.');

  if (ext == NULL) {
    strcpy(buf, DEFAULT_MIME_TYPE);
    return;
  }

  ext++;

  if (strcmp(ext, "html") == 0 || strcmp(ext, "htm") == 0) {
    strcpy(buf, "text/html");
  }
  if (strcmp(ext, "jpeg") == 0 || strcmp(ext, "jpg") == 0) {
    strcpy(buf, "image/jpg");
  }
  if (strcmp(ext, "css") == 0) {
    strcpy(buf, "text/css");
  }
  if (strcmp(ext, "js") == 0) {
    strcpy(buf, "application/javascript");
  }
  if (strcmp(ext, "json") == 0) {
    strcpy(buf, "application/json");
  }
  if (strcmp(ext, "txt") == 0) {
    strcpy(buf, "text/plain");
  }
  if (strcmp(ext, "gif") == 0) {
    strcpy(buf, "image/gif");
  }
  if (strcmp(ext, "png") == 0) {
    strcpy(buf, "image/png");
  }

  if (buf == NULL)
    strcpy(buf, DEFAULT_MIME_TYPE);
}
