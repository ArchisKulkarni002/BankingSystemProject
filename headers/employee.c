#include "employee.h"
#include "customer.h"
#include <unistd.h>
#include <stdio.h>

void employee_login(char* username, char* password){
    
}
void add_new_customer(Customer new_customer){
    char filepath[FPATH_SIZE];
    get_file_path(new_customer.id, filepath, sizeof(filepath));

    if (access(filepath, F_OK)==0){
        perror("The customer with that id already exists");
    }else{
        write_customer(new_customer);
    }
    
}
void modify_customer_details(int customer_id, Customer updated_customer){
    char filepath[FPATH_SIZE];
    get_file_path(customer_id, filepath, sizeof(filepath));
    
    write_customer(updated_customer);
}
void process_loan_application(int loan_id, int approve){
    
}
void view_customer_transactions(int customer_id){

}