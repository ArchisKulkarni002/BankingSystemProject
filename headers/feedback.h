#ifndef FEEDBACK_H
#define FEEDBACK_H
#define FDBACK_SIZE 2048

typedef struct {
    int feedback_id;
    int customer_id;
    char feedback_msg[FDBACK_SIZE];
}Feedback;

Feedback read_feedback(int feedback_id);
void write_feedback(int feedback_id, Feedback feedback);
void get_feedback_file(int id, char* filepath, int size);

#endif // FEEDBACK_H