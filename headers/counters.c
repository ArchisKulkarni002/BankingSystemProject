/*
 * Created by: Archis Kulkarni
 * Project Description: Bank Management System.
 */
#include "counters.h"
#include "file_utils.h"
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>

void get_counter_file(int id, char* filepath, int size){
    switch (id){
    case 4:
        snprintf(filepath, size, "counters/%s", "admin_counter");
        break;
    case 1:
        snprintf(filepath, size, "counters/%s", "customer_counter");
        break;
    case 2:
        snprintf(filepath, size, "counters/%s", "employee_counter");
        break;
    case 6:
        snprintf(filepath, size, "counters/%s", "feedback_counter");
        break;
    case 5:
        snprintf(filepath, size, "counters/%s", "loan_counter");
        break;
    case 3:
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
    int status = read(fd, &counter, sizeof(int));
    if (status == -1) {
        perror("Reading to file failed"); 
    }

    counter++;
    lseek(fd, 0, SEEK_SET);
    status = write(fd, &counter, sizeof(int));
    if (status == -1) {
        perror("Writing to file failed"); 
    }

    close_file(fd);
    return counter;
}

void reset_counters(){
    int counter = 1;
    for (int i = 0; i < 6; i++)
    {
        char filepath[FPATH_SIZE];
        get_counter_file(i+1, filepath, sizeof(filepath));

        int fd = open_file(filepath, O_RDWR|O_CREAT);

        lseek(fd, 0, SEEK_SET);
        int status = write(fd, &counter, sizeof(int));
        if (status == -1) {
            perror("Writing to file failed"); 
        }   
    }
    
}
