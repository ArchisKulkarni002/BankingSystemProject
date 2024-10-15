#include "manager.h"
#include "customer.h"
#include "feedback.h"
#include "loans.h"
#include "menus.h"
#include "file_utils.h"
#include<stdio.h>
#include<string.h>
#include<fcntl.h>

void manager_login(){
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

    Manager manager = read_manager(id);

    if (strcmp(manager.username, username)!=0 || strcmp(manager.password, password)!=0)
    {
        print_login_failure();
    }else{
        print_login_success("manager");
        logged_in=1;
        int choice;
        while (logged_in)
        {
            print_manager_menu();
            scanf("%d",&choice);
            switch (choice)
            {
            case 1:
                int customer_id;
                printf("Enter customer id for changing status: ");
                scanf("%d",&customer_id);
                Customer customer = read_customer(customer_id);
                if (customer.active_status==0)
                {
                    activate_deactivate_customer(customer.id, 1);
                    print_status("Customer account activated");
                }
                else if (customer.active_status==1)
                {
                    activate_deactivate_customer(customer.id, 0);
                    print_status("Customer account deactivated");
                }
                
                break;
            case 2:
                int loan_id;
                printf("Enter loan id to be assigned: ");
                scanf("%d",&loan_id);
                int employee_id;
                printf("Enter employee id for assigning loan: ");
                scanf("%d",&employee_id);

                assign_loan_to_employee(loan_id, employee_id);
                break;
            case 3:
                int feedback_id;
                printf("Enter feedback id for reviewing: ");
                scanf("%d",&feedback_id);
                review_feedback(feedback_id);
                break;
            case 4:
                char password_old[50], new_password[50], new_password1[50];
                printf("Enter current password: ");
                scanf("%s", password_old);
                if (strcmp(manager.password,password_old)!=0)
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

                Manager c = read_manager(manager.id);
                snprintf(c.password, sizeof(new_password), "%s", new_password);
                write_manager(c);
                break;
            case 6:
                logged_in=0;
                break;
            
            default:
                break;
            }
        }
        
    }
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

Manager read_manager(int id){
    char filepath[FPATH_SIZE];
    get_manager_file(id, filepath, sizeof(filepath));

    int fd = open_file(filepath, O_RDONLY|O_CREAT);   

    Manager manager;
    read_file(fd, (char*)&manager, sizeof(Manager));

    close_file(fd);

    return manager;
}
void write_manager(Manager manager){
    char filepath[FPATH_SIZE];
    get_manager_file(manager.id, filepath, sizeof(filepath));

    int fd = open_file(filepath, O_WRONLY|O_CREAT);

    write_file(fd, (char*)&manager, sizeof(Manager));
    close_file(fd);
}

void get_manager_file(int id, char* filepath, int size){
    snprintf(filepath, size, "managers/%d", id);
}