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
    int id, logged_in=0;
    char username[50]; 
    char password[50];

    printf("Enter employee id: ");
    scanf("%d", &id);
    getchar();
    
    printf("Enter user name: ");
    scanf("%s", username); 
    getchar();

    printf("Enter password: ");
    scanf("%s", password);
    getchar();

    Employee employee = read_employee(id);

    if (strcmp(employee.username, username)!=0 || strcmp(employee.password, password)!=0)
    {
        print_login_failure();
    }else{
        print_login_success("employee");
        logged_in=1;
        int choice;
        while (logged_in)
        {
            print_employee_menu();
            scanf("%d",&choice);
            switch (choice)
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
                add_new_customer(new_customer);
                break;
            case 2:
                printf("Funcaionality not done lolz!");
                break;
            case 3:
                int status, loan_id;
                print_subheading("Available loan statuses");
                printf("1.Pending 2.Approved 3.Rejected\n");
                printf("Enter loan id to be updated: ");
                scanf("%d",&loan_id);
                printf("Enter status to be updated: ");
                scanf("%d",&status);
                process_loan_application(loan_id, status);
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
                int customer_id;
                printf("Enter customer id for transaction history: ");
                scanf("%d",&customer_id);
                print_transaction_history(customer_id);                
                break;
            case 6:
                char password_old[50], new_password[50], new_password1[50];
                printf("Enter current password: ");
                scanf("%s", password_old);
                if (strcmp(employee.password,password_old)!=0)
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

                Employee c = read_employee(employee.id);
                snprintf(c.password, sizeof(new_password), "%s", new_password);
                write_employee(c);
                break;
            case 8:
                logged_in=0;
                break;
            
            default:
                break;
            }
        }
        
    }
}
void add_new_customer(Customer new_customer){
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