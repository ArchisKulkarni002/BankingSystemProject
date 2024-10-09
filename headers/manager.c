#include "manager.h"
#include "customer.h"
#include<stdio.h>

void manager_login(char* username, char* password){
    
}
void activate_deactivate_customer(int customer_id, int activate){   
    Customer c = read_customer(customer_id);
    c.active_status = activate;

    write_customer(c);
}
void assign_loan_to_employee(int loan_id, int employee_id){
    
}
void review_feedback(int feedback_id){

}

void get_manager_file(int id, char* filepath, int size){
    snprintf(filepath, size, "managers/%d", id);
}