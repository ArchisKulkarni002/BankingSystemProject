/*
 * Created by: Archis Kulkarni
 * Project Description: Bank Management System.
 */
#include "manager.h"
#include "customer.h"
#include "feedback.h"
#include "loans.h"
#include "menus.h"
#include "file_utils.h"
#include<stdio.h>
#include<string.h>
#include<fcntl.h>


void activate_deactivate_customer(int customer_id, int activate){   
    Customer c = read_customer(customer_id);
    c.active_status = activate;

    write_customer(c);
}
void assign_loan_to_employee(int loan_id, int employee_id){
    Loan loan = read_loan(loan_id);
    loan.assigned_employee_id=employee_id;
    write_loan(loan.loan_id, loan);
}

Manager read_manager(int id){
    char filepath[FPATH_SIZE];
    get_manager_file(id, filepath, sizeof(filepath));

    int fd = open_file(filepath, O_RDONLY|O_CREAT);   

    Manager manager;
    read_file(fd, (char*)&manager, sizeof(Manager));

    close_file(fd);

    return manager;
}
void write_manager(Manager manager){
    char filepath[FPATH_SIZE];
    get_manager_file(manager.id, filepath, sizeof(filepath));

    int fd = open_file(filepath, O_WRONLY|O_CREAT);

    write_file(fd, (char*)&manager, sizeof(Manager));
    close_file(fd);
}

void get_manager_file(int id, char* filepath, int size){
    snprintf(filepath, size, "managers/%d", id);
}