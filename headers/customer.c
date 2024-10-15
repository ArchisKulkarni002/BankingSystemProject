#include "customer.h"
#include "transactions.h"
#include "loans.h"
#include "feedback.h"
#include "menus.h"
#include "file_utils.h"
#include<fcntl.h>
#include<stdio.h>
#include<string.h>


void customer_login(){
    int id, logged_in=0;
    char username[50]; 
    char password[50];

    printf("Enter user id: ");
    scanf("%d", &id);
    getchar();
    
    printf("Enter user name: ");
    scanf("%s", username); 
    getchar();

    printf("Enter password: ");
    scanf("%s", password);
    getchar();

    Customer customer = read_customer(id);

    if (strcmp(customer.username, username)!=0 || strcmp(customer.password, password)!=0)
    {
        print_login_failure();
    }else{
        print_login_success("customer");
        logged_in=1;
        int choice;
        while (logged_in)
        {
            print_customer_menu();
            scanf("%d",&choice);
            switch (choice)
            {
            case 1:
                int bal=view_balance(customer.id);
                printf("Account balance: %d\n",bal);
                break;
            case 2:
                float deposit;
                printf("Enter amount to deposit: ");
                scanf("%f",&deposit);
                deposit_money(customer.id,deposit);
                break;
            case 3:
                float withdraw;
                printf("Enter amount to withdraw: ");
                scanf("%f",&withdraw);
                withdraw_money(customer.id,withdraw);
                break;
            case 4:
                float amount;
                int rec_id;
                printf("Enter amount to transfer: ");
                scanf("%f",&amount);
                printf("Enter account to transfer to: ");
                scanf("%d",&rec_id);
                transfer_funds(customer.id, rec_id,amount);
                break;
            case 5:
                printf("Funcaionality not done lolz!");
                
                break;
            case 6:
                char password_old[50], new_password[50], new_password1[50];
                printf("Enter current password: ");
                scanf("%s", password_old);
                if (strcmp(customer.password,password_old)!=0)
                {
                    printf("Incorrect password, exiting.");
                    break;
                }
                
                printf("Enter new password: ");
                scanf("%s", new_password);
                printf("Enter new password again1: ");
                scanf("%s", new_password1);

                if (strcmp(new_password,new_password1)!=0)
                {
                    printf("Passwords did not match, exiting.");
                    break;
                }

                Customer c = read_customer(customer.id);
                snprintf(c.password, sizeof(new_password), "%s", new_password);
                write_customer(c);
                break;
            case 8:
                print_transaction_history(customer.id);
                break;
            case 10:
                logged_in=0;
                break;
            
            default:
                break;
            }
        }
        
    }
    
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

void submit_feedback(int customer_id, int feedback_id, char* feedback_msg){
    Feedback feedback;
    feedback.feedback_id=feedback_id;
    feedback.customer_id = customer_id;
    snprintf(feedback.feedback_msg, FDBACK_SIZE, "%s", feedback_msg);
    write_feedback(feedback_id, feedback);
}

Customer read_customer(int id){
    char filepath[FPATH_SIZE];
    get_customer_file(id, filepath, sizeof(filepath));

    int fd = open_file(filepath, O_RDONLY|O_CREAT);   

    Customer customer;
    read_file(fd, (char*)&customer, sizeof(Customer));

    close_file(fd);
    return customer;
}
void write_customer(Customer customer){
    char filepath[FPATH_SIZE];
    get_customer_file(customer.id, filepath, sizeof(filepath));

    int fd = open_file(filepath, O_WRONLY|O_CREAT);

    write_file(fd, (char*)&customer, sizeof(Customer));
    close_file(fd);
}

void get_customer_file(int id, char* filepath, int size){
    snprintf(filepath, size, "customers/%d", id);
}