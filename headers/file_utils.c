#include "file_utils.h"
#include <fcntl.h>  
#include <unistd.h> 
#include <string.h> 
#include <stdio.h> 

int open_file(const char *filename, int flags) {
    int status = open(filename, flags, 0644);
    if (status == -1) {
        perror("Opening of file failed"); 
    }
    return status;
}

void read_file(int fd, char *buffer, size_t size) {
    int status = read(fd, buffer, size);
    if (status == -1) {
        perror("Reading to file failed"); 
    }
}

void write_file(int fd, const char *data, size_t size) {
    int status = write(fd, data, size);
    if (status == -1) {
        perror("Writing to file failed"); 
    }
}

void append_to_file(const char *filename, const char *data) {
    int fd = open(filename, O_WRONLY | O_APPEND | O_CREAT, 0644);
    if (fd == -1) {
        perror("Appending to file failed"); 
    }
    write_file(fd, data, strlen(data));
    close(fd); 
}
