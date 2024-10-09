#ifndef MANAGER_H
#define MANAGER_H

typedef struct{
    int id;
    char username[50];
    char password[50];
    int active_status;
}Manager;

void manager_login(char* username, char* password);
void activate_deactivate_customer(int customer_id, int activate);
void assign_loan_to_employee(int loan_id, int employee_id);
void review_feedback(int feedback_id);
void get_manager_file(int id, char* filepath, int size);

#endif // MANAGER_H