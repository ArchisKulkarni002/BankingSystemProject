#include "headers/customer.h"
#include "headers/manager.h"
#include "headers/employee.h"
#include "headers/admin.h"
#include "headers/transactions.h"
#include "headers/file_utils.h"
#include "headers/loans.h"
#include "headers/menus.h"
#include "headers/server.h"
#include "headers/counters.h"
#include "headers/feedback.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

int process_client(int client_fd);

int main() {
    int client_fd, new_socket;
    struct sockaddr_in address;
    int opt = 1;
    int addrlen = sizeof(address);

    // create socket
    if ((client_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        perror("Creating socket failed");
        exit(EXIT_FAILURE);
    }

    // set socket options
    setsockopt(client_fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));
    
    // configure address
    address.sin_family = AF_INET;
    address.sin_port = htons(SERVER_PORT);
    address.sin_addr.s_addr = inet_addr(SERVER_ADDR);

    if (connect(client_fd, (struct sockaddr*)&address, sizeof(address)) < 0) {
        perror("Connection to server failed");
        close(client_fd);
        exit(EXIT_FAILURE);
    }

    print_status("Connected to the bank server.");

    int status=1;
    while (status)
    {
        status = process_client(client_fd);
    }
    
    

}

int process_client(int client_fd) {
    char username[50], password[50];
    int role, id;
    print_heading("Welcome to Laxmi Chit Fund! Please login to continue");
    print_prelogin_prompt();
    scanf("%d", &role);
    printf("Enter id: ");
    scanf("%d", &id);
    printf("Enter username: ");
    scanf("%s", username);
    printf("Enter password: ");
    scanf("%s", password);

    write(client_fd, &role, sizeof(role));
    write(client_fd, &id, sizeof(id));
    write(client_fd, username, sizeof(username));
    write(client_fd, password, sizeof(password));

    int login_status;
    read(client_fd, &login_status, sizeof(int));

    if (login_status) {
        printf("Login successful!\n");
    } else {
        printf("Login failed!\n");
        exit(EXIT_FAILURE);
    }

    // perform operations based on roles
    while (1)
    {
        int operation;
        char password_old[50], new_password[50], new_password1[50];
        char message[2048];
        switch (role)
        {
        case C_CUSTOMER:
            Customer customer = read_customer(id);
            print_customer_menu();
            
            scanf("%d", &operation);
            switch (operation)
            {
                case 1:
                    int balance;
                    operation = 1;
                    write(client_fd, &operation, sizeof(int));
                    write(client_fd, &id, sizeof(int));
                    read(client_fd, &balance, sizeof(int)); 
                    printf("Account balance is: %d\n", balance);
                    break;
                case 2:
                    float deposit;
                    printf("Enter amount to deposit: ");
                    scanf("%f",&deposit);
                    operation = 2;
                    write(client_fd, &operation, sizeof(int));
                    write(client_fd, &id, sizeof(int));
                    write(client_fd, &deposit, sizeof(float));
                    read(client_fd, message, sizeof(char[2048]));
                    print_status(message);
                    break;
                case 3:
                    float withdraw;
                    printf("Enter amount to withdraw: ");
                    scanf("%f",&withdraw);
                    operation = 3;
                    write(client_fd, &operation, sizeof(int));
                    write(client_fd, &id, sizeof(int));
                    write(client_fd, &withdraw, sizeof(float));
                    read(client_fd, message, sizeof(char[2048]));
                    print_status(message);
                    break;
                case 4:
                    float amount;
                    int rec_id;
                    printf("Enter amount to transfer: ");
                    scanf("%f",&amount);
                    printf("Enter account to transfer to: ");
                    scanf("%d",&rec_id);

                    operation = 4;
                    write(client_fd, &operation, sizeof(int));
                    write(client_fd, &id, sizeof(int));
                    write(client_fd, &rec_id, sizeof(int));
                    write(client_fd, &amount, sizeof(float));
                    read(client_fd, message, sizeof(char[2048]));
                    print_status(message);

                    break;
                case 5:
                    float amount1;
                    printf("Enter amount for loan: ");
                    scanf("%f",&amount1);

                    operation = 12;
                    write(client_fd, &operation, sizeof(int));
                    write(client_fd, &id, sizeof(int));
                    write(client_fd, &amount1, sizeof(float));
                    read(client_fd, message, sizeof(char[2048]));
                    print_status(message);
                    break;
                case 6:
                    
                    printf("Enter current password: ");
                    scanf("%s", password_old);
                    
                    printf("Enter new password: ");
                    scanf("%s", new_password);
                    printf("Enter new password again1: ");
                    scanf("%s", new_password1);

                    operation=16;
                    write(client_fd, &operation, sizeof(int));
                    write(client_fd, &id, sizeof(int));
                    write(client_fd, &password_old, sizeof(password_old));
                    write(client_fd, &new_password, sizeof(new_password));
                    write(client_fd, &new_password1, sizeof(new_password1));
                    read(client_fd, message, sizeof(char[2048]));
                    print_status(message);
                    break;
                case 7:
                    Feedback feedback;
                    feedback.customer_id=id;
                    printf("Enter feedback: ");
                    scanf(" %[^\n]%*c",feedback.feedback_msg);

                    operation = 13;
                    write(client_fd, &operation, sizeof(int));
                    write(client_fd, &id, sizeof(int));
                    write(client_fd, &feedback, sizeof(Feedback));
                    read(client_fd, message, sizeof(char[2048]));
                    print_status(message);
                    break;
                case 8:
                    print_transaction_history(id);
                    break;
                case 9:
                    return 1;
                    break;
                case 10:
                    return 0;
                    break;
                
                default:
                    break;
            }
            break;

        case C_EMPLOYEE:
            Employee employee = read_employee(id);
            print_employee_menu();
            
            scanf("%d", &operation);

            switch (operation)
            {
                case 1:
                    Customer new_customer;
                    print_subheading("Fill the details for new customer");
                    printf("Enter username: ");
                    scanf("%s",new_customer.username);
                    printf("Enter password: ");
                    scanf("%s",new_customer.password);
                    new_customer.balance=0; 
                    new_customer.active_status=1;

                    operation = 5;
                    write(client_fd, &operation, sizeof(int));
                    write(client_fd, &id, sizeof(int));
                    write(client_fd, &new_customer, sizeof(Customer));
                    read(client_fd, message, sizeof(char[2048]));
                    print_status(message);
                    break;
                case 2:
                    int customer_id;
                    printf("Enter customer id to update: ");
                    scanf("%d",&customer_id);
                    char new_name[50];
                    print_subheading("Fill the details for new customer");
                    printf("Enter username: ");
                    scanf("%s",new_name);

                    operation = 6;
                    write(client_fd, &operation, sizeof(int));
                    write(client_fd, &id, sizeof(int));
                    write(client_fd, &customer_id, sizeof(int));
                    write(client_fd, &new_name, sizeof(new_name));
                    
                    read(client_fd, message, sizeof(char[2048]));
                    print_status(message);write(client_fd, new_name, sizeof(new_name));
                    break;
                case 3:
                    int status, loan_id;
                    print_subheading("Available loan statuses");
                    printf("1.Approved 2.Rejected\n");
                    printf("Enter loan id to be updated: ");
                    scanf("%d",&loan_id);
                    printf("Enter status to be updated: ");
                    scanf("%d",&status);

                    operation = 7;
                    write(client_fd, &operation, sizeof(int));
                    write(client_fd, &id, sizeof(int));
                    write(client_fd, &loan_id, sizeof(int));
                    write(client_fd, &status, sizeof(int));
                    read(client_fd, message, sizeof(char[2048]));
                    print_status(message);
                    break;
                case 4:
                    int loan_id1;
                    printf("Enter loan id to be viewed: ");
                    scanf("%d",&loan_id1);
                    Loan loan = read_loan(loan_id1);

                    printf("Loan ID: %d\n", loan.loan_id);
                    printf("Loan Amount: %f\n", loan.amount);
                    printf("Customer ID: %d\n", loan.customer_id);
                    printf("Assigned employee ID: %d\n", loan.assigned_employee_id);
                    printf("Status: %d\n", loan.status);
                    break;
                case 5:
                    int customer_id1;
                    printf("Enter customer id for transaction history: ");
                    scanf("%d",&customer_id1);
                    print_transaction_history(customer_id1);
                    break;
                case 6:
                    
                    printf("Enter current password: ");
                    scanf("%s", password_old);
                    
                    printf("Enter new password: ");
                    scanf("%s", new_password);
                    printf("Enter new password again1: ");
                    scanf("%s", new_password1);

                    operation=17;
                    write(client_fd, &operation, sizeof(int));
                    write(client_fd, &id, sizeof(int));
                    write(client_fd, &password_old, sizeof(password_old));
                    write(client_fd, &new_password, sizeof(new_password));
                    write(client_fd, &new_password1, sizeof(new_password1));
                    read(client_fd, message, sizeof(char[2048]));
                    print_status(message);
                    break;
                case 7:
                    return 1;
                    break;
                case 8:
                    return 0;
                    break;
                
                default:
                    break;
            }
            break;
        case C_MANAGER:
            Manager manager = read_manager(id);
            print_manager_menu();
            
            scanf("%d", &operation);
            switch (operation)
            {
                case 1:
                    int customer_id;
                    printf("Enter customer id for changing status: ");
                    scanf("%d",&customer_id);

                    operation = 8;
                    write(client_fd, &operation, sizeof(int));
                    write(client_fd, &id, sizeof(int));
                    write(client_fd, &customer_id, sizeof(int));
                    read(client_fd, message, sizeof(char[2048]));
                    print_status(message);
                    break;
                case 2:
                    int loan_id;
                    printf("Enter loan id to be assigned: ");
                    scanf("%d",&loan_id);
                    int employee_id;
                    printf("Enter employee id for assigning loan: ");
                    scanf("%d",&employee_id);

                    operation = 9;
                    write(client_fd, &operation, sizeof(int));
                    write(client_fd, &id, sizeof(int));
                    write(client_fd, &loan_id, sizeof(int));
                    write(client_fd, &employee_id, sizeof(int));
                    read(client_fd, message, sizeof(char[2048]));
                    print_status(message);
                    break;
                case 3:
                    int feedback_id;
                    Feedback feedback;
                    printf("Enter feedback id for reviewing: ");
                    scanf("%d",&feedback_id);

                    operation = 10;
                    write(client_fd, &operation, sizeof(int));
                    write(client_fd, &id, sizeof(int));
                    write(client_fd, &loan_id, sizeof(int));
                    read(client_fd, &feedback, sizeof(Feedback));

                    printf("Feedback number: %d\n",feedback.feedback_id);
                    printf("Customer number: %d\n",feedback.customer_id);
                    printf("Feedback: %s\n",feedback.feedback_msg);
                    break;
                case 4:
                    
                    printf("Enter current password: ");
                    scanf("%s", password_old);
                    
                    printf("Enter new password: ");
                    scanf("%s", new_password);
                    printf("Enter new password again1: ");
                    scanf("%s", new_password1);

                    operation=18;
                    write(client_fd, &operation, sizeof(int));
                    write(client_fd, &id, sizeof(int));
                    write(client_fd, &password_old, sizeof(password_old));
                    write(client_fd, &new_password, sizeof(new_password));
                    write(client_fd, &new_password1, sizeof(new_password1));
                    read(client_fd, message, sizeof(char[2048]));
                    print_status(message);
                    break;
                case 5:
                    return 1;
                    break;
                case 6:
                    return 0;
                    break;
                
                default:
                    break;
            }
            break;
        case C_ADMIN:
            Admin admin = read_admin(id);
            print_admin_menu();
            
            scanf("%d", &operation);
            switch (operation)
            {
                case 1:
                    Employee new_employee; 
                    print_subheading("Fill the details for new employee");
                    printf("Enter username: ");
                    scanf("%s",new_employee.username);
                    printf("Enter password: ");
                    scanf("%s",new_employee.password);
                    new_employee.active_status=1;

                    operation=11;
                    write(client_fd, &operation, sizeof(int));
                    write(client_fd, &id, sizeof(int));
                    write(client_fd, &new_employee, sizeof(Employee));
                    read(client_fd, message, sizeof(char[2048]));
                    print_status(message);
                    break;
                case 2:
                    int employee_id;
                    printf("Enter employee id to update: ");
                    scanf("%d",&employee_id);
                    char new_name[50];
                    print_subheading("Fill the details for new employee");
                    printf("Enter username: ");
                    scanf("%s",new_name);

                    operation = 14;
                    write(client_fd, &operation, sizeof(int));
                    write(client_fd, &id, sizeof(int));
                    write(client_fd, &employee_id, sizeof(int));
                    write(client_fd, new_name, sizeof(new_name));
                    read(client_fd, message, sizeof(char[2048]));
                    print_status(message);
                    break;
                case 3:
                    int employee_id1;
                    printf("Enter employee id to promote to manager: ");
                    scanf("%d",&employee_id1);

                    operation = 15;
                    write(client_fd, &operation, sizeof(int));
                    write(client_fd, &id, sizeof(int));
                    write(client_fd, &employee_id1, sizeof(int));
                    read(client_fd, message, sizeof(char[2048]));
                    print_status(message);
                    break;
                case 4:
                    
                    printf("Enter current password: ");
                    scanf("%s", password_old);
                    
                    printf("Enter new password: ");
                    scanf("%s", new_password);
                    printf("Enter new password again1: ");
                    scanf("%s", new_password1);

                    operation=19;
                    write(client_fd, &operation, sizeof(int));
                    write(client_fd, &id, sizeof(int));
                    write(client_fd, &password_old, sizeof(password_old));
                    write(client_fd, &new_password, sizeof(new_password));
                    write(client_fd, &new_password1, sizeof(new_password1));
                    read(client_fd, message, sizeof(char[2048]));
                    print_status(message);
                    break;
                case 5:
                    return 1;
                    break;
                case 6:
                    return 0;
                    break;
                case 7:
                    operation=20;
                    write(client_fd, &operation, sizeof(int));
                    write(client_fd, &id, sizeof(int));
                    read(client_fd, message, sizeof(char[2048]));
                    print_status(message);
                    break;
                
                default:
                    break;
            }
            break;
        
        default:
            break;
        }
    }
    
}