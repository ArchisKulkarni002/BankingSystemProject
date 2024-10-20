#include "headers/customer.h"
#include "headers/manager.h"
#include "headers/employee.h"
#include "headers/admin.h"
#include "headers/loans.h"
#include "headers/file_utils.h"
#include "headers/menus.h"
#include "headers/counters.h"
#include "headers/feedback.h"
#include "headers/server.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>

void handle_client(int client_socket);
int authenticate_user(int role, int id, char *username, char *password);
void perform_operation(int client_socket, int operation);

int main() {
    
    server_config_struct config = setup_server();
    int new_socket;
    socklen_t addr_len = sizeof(config.address);
    
    while (1) {
        // accept new connection
        if ((new_socket = accept(config.server_fd, (struct sockaddr *)&config.address, &addr_len)) < 0) {
            perror("Error accepting connection.");
            continue;
        }

        // fork a new process to handle the client
        if (fork() == 0) {
            // In child process
            close(config.server_fd);
            handle_client(new_socket);
            close(new_socket);
            exit(0);
        }
        close(new_socket); 
    }

    return 0;
}

void handle_client(int client_socket) {
    char username[50], password[50];
    
    int role, id;

    // Read login credentials from client
    read(client_socket, &role, sizeof(role));
    read(client_socket, &id, sizeof(id));
    read(client_socket, username, sizeof(username));
    read(client_socket, password, sizeof(password));

    // Authenticate user
    int login_status = authenticate_user(role, id, username, password);
    write(client_socket, &login_status, sizeof(int));

    int operation;
    while (read(client_socket, &operation, sizeof(int)) > 0) {
        perform_operation(client_socket, operation);
    }
}

int authenticate_user(int role, int id, char *username, char *password) {
    switch (role)
    {
    case C_CUSTOMER:
        Customer customer = read_customer(id);
        if (strcmp(customer.username, username)!=0 || strcmp(customer.password, password)!=0)
        {
            print_login_failure();
            return 0;
        }
        print_login_success("customer");
        return 1;
        break;
    case C_EMPLOYEE:
        Employee employee = read_employee(id);
        if (strcmp(employee.username, username)!=0 || strcmp(employee.password, password)!=0)
        {
            print_login_failure();
            return 0;
        }
        print_login_success("employee");
        return 1;
        break;
    case C_MANAGER:
        Manager manager = read_manager(id);
        if (strcmp(manager.username, username)!=0 || strcmp(manager.password, password)!=0)
        {
            print_login_failure();
            return 0;
        }
        print_login_success("manager");
        return 1;
        break;
    case C_ADMIN:
        Admin admin = read_admin(id);
        if (strcmp(admin.username, username)!=0 || strcmp(admin.password, password)!=0)
        {
            print_login_failure();
            return 0;
        }
        print_login_success("admin");
        return 1;
        break;
    
    default:
        break;
    }
}

void perform_operation(int client_socket, int operation){
    int id;
    char password_old[50], new_password[50], new_password1[50];
    switch (operation) {
        case 1:
            read(client_socket, &id, sizeof(int));
            int balance = view_balance(id);
            write(client_socket, &balance, sizeof(int));
            break;
        case 2:
            float deposit;
            read(client_socket, &id, sizeof(int));
            read(client_socket, &deposit, sizeof(float));
            deposit_money(id, deposit);
            break;
        case 3:
            float withdraw;
            read(client_socket, &id, sizeof(int));
            read(client_socket, &withdraw, sizeof(float));
            withdraw_money(id, withdraw);
            break;
        case 4:
            int rec_id;
            float amount;
            read(client_socket, &id, sizeof(int));
            read(client_socket, &rec_id, sizeof(int));
            read(client_socket, &amount, sizeof(float));
            transfer_funds(id, rec_id, amount);
            break;
        case 5:
            Customer customer;
            read(client_socket, &id, sizeof(int));
            read(client_socket, &customer, sizeof(Customer));
            add_new_customer(customer);
            break;
        case 6:
            int customer_id;
            char new_name[50];
            read(client_socket, &id, sizeof(int));
            read(client_socket, &customer_id, sizeof(int));
            read(client_socket, &new_name, sizeof(new_name));

            Customer updated = read_customer(customer_id);
            snprintf(updated.username, sizeof(new_name), "%s", new_name);
            write_customer(updated);

            break;
        case 7:
            int loan_id, status;
            read(client_socket, &id, sizeof(int));
            read(client_socket, &loan_id, sizeof(int));
            read(client_socket, &status, sizeof(int));
            process_loan_application(loan_id, status);
            break;
        case 8:
            int custmoer_id;
            read(client_socket, &id, sizeof(int));
            read(client_socket, &custmoer_id, sizeof(int));
            Customer cusotmer = read_customer(custmoer_id);
            if (customer.active_status==0)
            {
                activate_deactivate_customer(customer.id, 1);
            }
            else if (customer.active_status==1)
            {
                activate_deactivate_customer(customer.id, 0);
            }
            break;
        case 9:
            int loan_id1, employee_id;
            read(client_socket, &id, sizeof(int));
            read(client_socket, &loan_id1, sizeof(int));
            read(client_socket, &employee_id, sizeof(int));
            assign_loan_to_employee(loan_id1, employee_id);
            break;
        case 10:
            int feedback_id;
            read(client_socket, &id, sizeof(int));
            read(client_socket, &loan_id, sizeof(int));
            read(client_socket, &feedback_id, sizeof(int));
            Feedback feedback = read_feedback(feedback_id);
            break;
        case 11:
            Employee employee;
            read(client_socket, &id, sizeof(int));
            read(client_socket, &employee, sizeof(Employee));
            add_new_employee(employee);
            break;
        case 12:
            float amount1;
            read(client_socket, &id, sizeof(int));
            read(client_socket, &amount1, sizeof(float));

            Loan loan;
            loan.loan_id = get_new_count(C_LOAN);
            loan.customer_id=id;
            loan.assigned_employee_id=0;
            loan.status=1;
            loan.amount=amount1;

            write_loan(loan.loan_id, loan);

            break;
        case 13:
            Feedback feedback1;
            read(client_socket, &id, sizeof(int));
            read(client_socket, &feedback1, sizeof(Feedback));
            feedback1.feedback_id = get_new_count(C_FEEDBACK);
            write_feedback(feedback1.feedback_id, feedback1);
            break;
        case 14:
            int employee_id2;
            char new_name1[50];
            read(client_socket, &id, sizeof(int));
            read(client_socket, &employee_id2, sizeof(int));
            read(client_socket, &new_name1, sizeof(new_name1));

            Employee updated1 = read_employee(employee_id2);
            snprintf(updated1.username, sizeof(new_name1), "%s", new_name1);
            write_employee(updated1);
            break;
        case 15:
            int employee_id1;
            read(client_socket, &id, sizeof(int));
            read(client_socket, &employee_id1, sizeof(int));

            Employee updated2 = read_employee(employee_id1);
            Manager new_manager;
            new_manager = *(Manager*)&updated2;
            new_manager.id = get_new_count(C_MANAGER);
            write_manager(new_manager);
            break;
        case 16:
            read(client_socket, &id, sizeof(int));
            read(client_socket, &password_old, sizeof(password_old));
            read(client_socket, &new_password, sizeof(new_password));
            read(client_socket, &new_password1, sizeof(new_password1));
            Customer pass = read_customer(id);
            if (strcmp(pass.password,password_old)!=0)
            {
                printf("Incorrect password, exiting.");
            }else{

                if (strcmp(new_password,new_password1)!=0)
                {
                    printf("Passwords did not match, exiting.");
                }else{
                    snprintf(pass.password, sizeof(new_password), "%s", new_password);
                    write_customer(pass);
                }
            }
            break;
        case 17:
            read(client_socket, &id, sizeof(int));
            read(client_socket, &password_old, sizeof(password_old));
            read(client_socket, &new_password, sizeof(new_password));
            read(client_socket, &new_password1, sizeof(new_password1));
            Employee pass1 = read_employee(id);
            if (strcmp(pass1.password,password_old)!=0)
            {
                printf("Incorrect password, exiting.");
            }else{

                if (strcmp(new_password,new_password1)!=0)
                {
                    printf("Passwords did not match, exiting.");
                }else{
                    snprintf(pass1.password, sizeof(new_password), "%s", new_password);
                    write_employee(pass1);
                }
            }
            break;
        case 18:
            read(client_socket, &id, sizeof(int));
            read(client_socket, &password_old, sizeof(password_old));
            read(client_socket, &new_password, sizeof(new_password));
            read(client_socket, &new_password1, sizeof(new_password1));
            Manager pass2 = read_manager(id);
            if (strcmp(pass2.password,password_old)!=0)
            {
                printf("Incorrect password, exiting.");
            }else{

                if (strcmp(new_password,new_password1)!=0)
                {
                    printf("Passwords did not match, exiting.");
                }else{
                    snprintf(pass2.password, sizeof(new_password), "%s", new_password);
                    write_manager(pass2);
                }
            }
            break;
        case 19:
            read(client_socket, &id, sizeof(int));
            read(client_socket, &password_old, sizeof(password_old));
            read(client_socket, &new_password, sizeof(new_password));
            read(client_socket, &new_password1, sizeof(new_password1));
            Admin pass3 = read_admin(id);
            if (strcmp(pass3.password,password_old)!=0)
            {
                printf("Incorrect password, exiting.");
            }else{

                if (strcmp(new_password,new_password1)!=0)
                {
                    printf("Passwords did not match, exiting.");
                }else{
                    snprintf(pass3.password, sizeof(new_password), "%s", new_password);
                    write_admin(pass3);
                }
            }
            break;
        case 20:
            // Code for case 20
            break;
        default:
            // Code for default case
            break;
    }

}