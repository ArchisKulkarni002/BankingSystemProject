#include <stddef.h>
#include <unistd.h>
#define FPATH_SIZE 100
#define LOGGING 0

int open_file(const char *filename, int flags);
void close_file(int fd);
void read_file(int fd, char *buffer, size_t size);
void write_file(int fd, const char *data, size_t size);
void append_to_file(const char *filename, const char *data);