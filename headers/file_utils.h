#include <stddef.h>
#include <unistd.h>


int open_file(const char *filename, int flags);
void read_file(int fd, char *buffer, size_t size);
void write_file(int fd, const char *data, size_t size);
void append_to_file(const char *filename, const char *data);