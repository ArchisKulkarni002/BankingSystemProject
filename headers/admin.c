#include "admin.h"
#include "employee.h"
#include "counters.h"
#include "file_utils.h"
#include "menus.h"
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <fcntl.h>

void admin_login(){
    int id, logged_in=0;
    char username[50]; 
    char password[50];

    printf("Enter admin id: ");
    scanf("%d", &id);
    getchar();
    
    printf("Enter user name: ");
    scanf("%s", username); 
    getchar();

    printf("Enter password: ");
    scanf("%s", password);
    getchar();

    Admin admin = read_admin(id);

    if (strcmp(admin.username, username)!=0 || strcmp(admin.password, password)!=0)
    {
        print_login_failure();
    }else{
        print_login_success("admin");
        logged_in=1;
        int choice;
        while (logged_in)
        {
            print_admin_menu();
            scanf("%d",&choice);
            switch (choice)
            {
            case 1:
                Employee new_employee; 
                print_subheading("Fill the details for new employee");
                printf("Enter username: ");
                scanf("%s",new_employee.username);
                printf("Enter password: ");
                scanf("%s",new_employee.password);
                new_employee.active_status=1;
                add_new_employee(new_employee);
                break;
            case 2:
                // int loan_id;
                // printf("Enter loan id to be assigned: ");
                // scanf("%d",&loan_id);
                // int admin_id;
                // printf("Enter admin id for assigning loan: ");
                // scanf("%d",&admin_id);

                // assign_loan_to_admin(loan_id, admin_id);
                break;
            case 3:
                // int feedback_id;
                // printf("Enter feedback id for reviewing: ");
                // scanf("%d",&feedback_id);
                // review_feedback(feedback_id);
                break;
            case 4:
                char password_old[50], new_password[50], new_password1[50];
                printf("Enter current password: ");
                scanf("%s", password_old);
                if (strcmp(admin.password,password_old)!=0)
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

                Admin c = read_admin(admin.id);
                snprintf(c.password, sizeof(new_password), "%s", new_password);
                write_admin(c);
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
void add_new_employee(Employee new_employee){
    char filepath[FPATH_SIZE];

    int new_employee_id = get_new_count(C_EMPLOYEE);
    new_employee.id=new_employee_id;

    get_employee_file(new_employee.id, filepath, sizeof(filepath));

    if (access(filepath, F_OK)==0){
        perror("The employee with that id already exists");
    }else{
        write_employee(new_employee);
        printf("New employee created with ID: %d\n", new_employee_id);
    }
}
void modify_user_details(int user_id, char* new_username, char* new_password){
    
}
void manage_user_roles(int user_id, char* new_role){

}

Admin read_admin(int id){
    char filepath[FPATH_SIZE];
    get_admin_file(id, filepath, sizeof(filepath));

    int fd = open_file(filepath, O_RDONLY|O_CREAT);   

    Admin admin;
    read_file(fd, (char*)&admin, sizeof(Admin));

    close_file(fd);

    return admin;
}
void write_admin(Admin admin){
    char filepath[FPATH_SIZE];
    get_admin_file(admin.id, filepath, sizeof(filepath));

    int fd = open_file(filepath, O_WRONLY|O_CREAT);

    write_file(fd, (char*)&admin, sizeof(Admin));
    close_file(fd);
}

void get_admin_file(int id, char* filepath, int size){
    snprintf(filepath, size, "admins/%d", id);
}