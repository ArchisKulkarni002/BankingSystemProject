#include "counters.h"
#include "file_utils.h"
#include <fcntl.h>
#include <stdio.h>

void get_counter_file(int id, char* filepath, int size){
    switch (id){
    case 0:
        snprintf(filepath, size, "counters/%s", "admin_counter");
        break;
    case 1:
        snprintf(filepath, size, "counters/%s", "customer_counter");
        break;
    case 2:
        snprintf(filepath, size, "counters/%s", "employee_counter");
        break;
    case 3:
        snprintf(filepath, size, "counters/%s", "feedback_counter");
        break;
    case 4:
        snprintf(filepath, size, "counters/%s", "loan_counter");
        break;
    case 5:
        snprintf(filepath, size, "counters/%s", "manager_counter");
        break;
    
    default:
        break;
    }
    
}
int get_new_count(int id){
    char filepath[FPATH_SIZE];
    get_counter_file(id, filepath, sizeof(filepath));

    int fd = open_file(filepath, O_RDWR|O_CREAT);   

    int counter;
    read_file(fd, (char*)&counter, sizeof(int));

    counter++;
    lseek(fd, 0, SEEK_SET);
    write_file(fd, (char*)&counter, sizeof(int));

    close_file(fd);
    return counter;
}
