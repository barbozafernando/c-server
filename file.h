#ifndef _FILE_H_
#define _FILE_H_

#define FILE_MAX_SIZE 65536 // 64K

const char *get_filename_from_request(char *buf);
char *read_file(const char *filename);

#endif
