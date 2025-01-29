#ifndef _FILE_H_
#define _FILE_H_

#define FILE_MAX_SIZE (64*1024)
#define FILENAME_MAX_SIZE 256

void get_filename_from_request(char *buf, const char* filenamebuf);
void read_file(const char *filename, char *filecontentbuf);

#endif
