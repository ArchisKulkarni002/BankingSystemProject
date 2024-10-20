#include "customer.h"
#ifndef EMPLOYEE_H
#define EMPLOYEE_H

typedef struct{
    int id;
    char username[50];
    char password[50];
    int active_status;
}Employee;

void employee_login();
int add_new_customer(Customer new_customer);
void modify_customer_details(int customer_id, Customer updated_customer);
void process_loan_application(int loan_id, int approve);
Employee read_employee(int id);
void write_employee(Employee employee);
void get_employee_file(int id, char* filepath, int size);

#endif // EMPLOYEE_H