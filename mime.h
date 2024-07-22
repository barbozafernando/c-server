#ifndef _MIME_H_
#define _MIME_H_

#define DEFAULT_MIME_TYPE "text/html"
#define MIME_TYPE_SIZE 50

void get_mime_type(const char *filename, char buf[]);

#endif
