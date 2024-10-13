#include "feedback.h"
#include "file_utils.h"
#include <fcntl.h>
#include <stdio.h>

Feedback read_feedback(int feedback_id){
    char filepath[FPATH_SIZE];
    get_feedback_file(feedback_id, filepath, sizeof(filepath));

    int fd = open_file(filepath, O_RDONLY|O_CREAT);   

    Feedback feedback;
    read_file(fd, (char*)&feedback, sizeof(feedback));

    close_file(fd);

    return feedback;
}
void write_feedback(int feedback_id, Feedback feedback){
    char filepath[FPATH_SIZE];
    get_feedback_file(feedback_id, filepath, sizeof(filepath));

    int fd = open_file(filepath, O_WRONLY|O_CREAT);   

    write_file(fd, (char*)&feedback, sizeof(feedback));

    close_file(fd);
}
void get_feedback_file(int id, char* filepath, int size){
    snprintf(filepath, size, "feedbacks/%d", id);
}