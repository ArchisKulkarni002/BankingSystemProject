/*
 * Created by: Archis Kulkarni
 * Project Description: Bank Management System.
 */
#include "employee.h"
#include "customer.h"
#include "file_utils.h"
#include "menus.h"
#include "transactions.h"
#include "loans.h"
#include "counters.h"
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <fcntl.h>

void employee_login(){
    //         case 6:
    //             char password_old[50], new_password[50], new_password1[50];
    //             printf("Enter current password: ");
    //             scanf("%s", password_old);
    //             if (strcmp(employee.password,password_old)!=0)
    //             {
    //                 printf("Incorrect password, exiting.");
    //                 break;
    //             }
                
    //             printf("Enter new password: ");
    //             scanf("%s", new_password);
    //             printf("Enter new password again1: ");
    //             scanf("%s", new_password1);

    //             if (strcmp(new_password,new_password1)!=0)
    //             {
    //                 printf("Passwords did not match, exiting.");
    //                 break;
    //             }

    //             Employee c = read_employee(employee.id);
    //             snprintf(c.password, sizeof(new_password), "%s", new_password);
    //             write_employee(c);

}
int add_new_customer(Customer new_customer){
    char filepath[FPATH_SIZE];
    
    int new_customer_id = get_new_count(C_CUSTOMER);
    new_customer.id=new_customer_id;

    get_customer_file(new_customer.id, filepath, sizeof(filepath));

    if (access(filepath, F_OK)==0){
        perror("The customer with that id already exists");
    }else{
        write_customer(new_customer);
        printf("New customer created with ID: %d\n", new_customer_id);
    }

    return new_customer.id;
}
void modify_customer_details(int customer_id, Customer updated_customer){    
    write_customer(updated_customer);
}
void process_loan_application(int loan_id, int status){
    update_status(loan_id, status);
    printf("** Updated loan application %d to status %d **", loan_id, status);
}

Employee read_employee(int id){
    char filepath[FPATH_SIZE];
    get_employee_file(id, filepath, sizeof(filepath));

    int fd = open_file(filepath, O_RDONLY|O_CREAT);   

    Employee employee;
    read_file(fd, (char*)&employee, sizeof(Employee));

    close_file(fd);

    return employee;
}
void write_employee(Employee employee){
    char filepath[FPATH_SIZE];
    get_employee_file(employee.id, filepath, sizeof(filepath));

    int fd = open_file(filepath, O_WRONLY|O_CREAT);

    write_file(fd, (char*)&employee, sizeof(Employee));
    close_file(fd);
}

void get_employee_file(int id, char* filepath, int size){
    snprintf(filepath, size, "employees/%d", id);
}