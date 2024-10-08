#include "customer.h"
#ifndef EMPLOYEE_H
#define EMPLOYEE_H

typedef struct{
    int id;
    char username[50];
    char password[50];
    int active_status;
}Employee;

void employee_login(char* username, char* password);
void add_new_customer(Customer new_customer);
void modify_customer_details(int customer_id, Customer updated_customer);
void process_loan_application(int loan_id, int approve);
void view_customer_transactions(int customer_id);

#endif // EMPLOYEE_H