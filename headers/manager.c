#include "manager.h"
#include "customer.h"
#include "feedback.h"
#include "loans.h"
#include<stdio.h>

void manager_login(char* username, char* password){
    
}
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
void review_feedback(int feedback_id){
    Feedback feedback = read_feedback(feedback_id);
    printf("Feedback number: %d\n",feedback.feedback_id);
    printf("Customer number: %d\n",feedback.customer_id);
    printf("Feedback: %s\n",feedback.feedback_msg);
}

void get_manager_file(int id, char* filepath, int size){
    snprintf(filepath, size, "managers/%d", id);
}