#include "file_utils.h"
#include "menus.h"
#include<fcntl.h>
#include<sys/file.h>
#include<stdio.h>
#include<unistd.h>
#include<string.h>

int open_file(const char *filename, int flags) {
    int status = open(filename, flags, 0644);
    if (status == -1) {
        perror("Opening of file failed"); 
    }

    // Try to acquire an exclusive lock (LOCK_EX) and wait (blocking)
    int lock_status = flock(status, LOCK_EX);
    if (lock_status == -1) {
        perror("Locking of file failed");
        close(status);
        return -1;
    }
    log_info("file lock acquired");
    return status;
}

void close_file(int fd) {
    int lock_status = flock(fd, LOCK_UN);
    if (lock_status == -1) {
        perror("Unlocking of file failed");
    }

    log_info("file lock released");
    
    // Close the file
    if (close(fd) == -1) {
        perror("Closing of file failed");
    }
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
