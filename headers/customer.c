#include "customer.h"
#include "transactions.h"
#include "loans.h"
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

    Transaction transaction;
    transaction.amount=amount;
    transaction.sender_id=customer_id;
    transaction.receiver_id=customer_id;
    transaction.type=1;
    record_transaction(transaction);
}
void withdraw_money(int customer_id, float amount){
    Customer c = read_customer(customer_id);
    c.balance-=amount;
    write_customer(c);

    Transaction transaction;
    transaction.amount=amount;
    transaction.sender_id=customer_id;
    transaction.receiver_id=customer_id;
    transaction.type=-1;
    record_transaction(transaction);
}
void transfer_funds(int sender_id, int receiver_id, float amount){
    Customer sender, receiver;
    sender=read_customer(sender_id);
    receiver=read_customer(receiver_id);

    sender.balance-=amount;
    receiver.balance+=amount;

    write_customer(sender);
    write_customer(receiver);

    Transaction transaction;
    transaction.amount=amount;
    transaction.sender_id=sender_id;
    transaction.receiver_id=receiver_id;
    transaction.type=0;
    record_transaction(transaction);

    printf("Transfered %f rupees from %d account to %d account.\n", amount, sender_id, receiver_id);
}
void apply_loan(int customer_id, float loan_amount){
    Loan loan;
    loan.customer_id=customer_id;
    loan.amount=loan_amount;
    loan.status=0;
}

void submit_feedback(int customer_id, char* feedback){
    
}

Customer read_customer(int id){
    char filepath[FPATH_SIZE];
    get_customer_file(id, filepath, sizeof(filepath));

    int fd = open_file(filepath, O_RDONLY|O_CREAT);   

    Customer customer;
    read_file(fd, (char*)&customer, sizeof(Customer));

    return customer;
}
void write_customer(Customer customer){
    char filepath[FPATH_SIZE];
    get_customer_file(customer.id, filepath, sizeof(filepath));

    int fd = open_file(filepath, O_WRONLY|O_CREAT);

    write_file(fd, (char*)&customer, sizeof(Customer));
}

void get_customer_file(int id, char* filepath, int size){
    snprintf(filepath, size, "customers/%d", id);
}