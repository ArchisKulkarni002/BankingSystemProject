#include "employee.h"
#include "customer.h"
#include "file_utils.h"
#include "loans.h"
#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>

void employee_login(char* username, char* password){
    
}
void add_new_customer(Customer new_customer){
    char filepath[FPATH_SIZE];
    get_customer_file(new_customer.id, filepath, sizeof(filepath));

    if (access(filepath, F_OK)==0){
        perror("The customer with that id already exists");
    }else{
        write_customer(new_customer);
    }
    
}
void modify_customer_details(int customer_id, Customer updated_customer){    
    write_customer(updated_customer);
}
void process_loan_application(int loan_id, int approve){
    update_status(loan_id, 1);
}

Employee read_employee(int id){
    char filepath[FPATH_SIZE];
    get_customer_file(id, filepath, sizeof(filepath));

    int fd = open_file(filepath, O_RDONLY|O_CREAT);   

    Employee employee;
    read_file(fd, (char*)&employee, sizeof(Employee));

    close_file(fd);

    return employee;
}
void write_employee(Employee employee){
    char filepath[FPATH_SIZE];
    get_customer_file(employee.id, filepath, sizeof(filepath));

    int fd = open_file(filepath, O_WRONLY|O_CREAT);

    write_file(fd, (char*)&employee, sizeof(Employee));
    close_file(fd);
}

void get_employee_file(int id, char* filepath, int size){
    snprintf(filepath, size, "employees/%d", id);
}