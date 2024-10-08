#include "customer.h"
#include "file_utils.h"
#include<fcntl.h>
#include<stdio.h>


void customer_login(char* username, char* password){
    
}
float view_balance(int customer_id){
    Customer c = read_customer(customer_id);
    return c.balance;
}
void deposit_money(int customer_id, float amount){
    Customer c = read_customer(customer_id);
    c.balance+=amount;
    write_customer(c);
}
void withdraw_money(int customer_id, float amount){
    Customer c = read_customer(customer_id);
    c.balance-=amount;
    write_customer(c);
}
void transfer_funds(int sender_id, int receiver_id, float amount){
    
}
void apply_loan(int customer_id, float loan_amount){
    
}
void view_transaction_history(int customer_id){
    
}
void submit_feedback(int customer_id, char* feedback){
    
}

Customer read_customer(int id){
    char filepath[FPATH_SIZE];
    get_file_path(id, filepath, sizeof(filepath));

    int fd = open_file(filepath, O_RDONLY|O_CREAT);   

    Customer customer;
    read_file(fd, (char*)&customer, sizeof(Customer));

    return customer;
}
void write_customer(Customer customer){
    char filepath[FPATH_SIZE];
    get_file_path(customer.id, filepath, sizeof(filepath));

    int fd = open_file(filepath, O_WRONLY|O_CREAT);

    write_file(fd, (char*)&customer, sizeof(Customer));
}

void get_file_path(int id, char* filepath, int size){
    snprintf(filepath, size, "customers/%d", id);
}