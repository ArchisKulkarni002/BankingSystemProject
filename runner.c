#include "headers/customer.h"
#include "headers/employee.h"
#include "headers/manager.h"
#include "headers/admin.h"
#include "headers/menus.h"
#include "headers/counters.h"
#include<string.h>
#include<stdio.h>

void addAdmin(){
    Admin new_admin; 
    print_subheading("Fill the details for new admin");
    printf("Enter username: ");
    scanf("%s",new_admin.username);
    printf("Enter password: ");
    scanf("%s",new_admin.password);
    new_admin.active_status=1;
    int new_admin_id = get_new_count(C_ADMIN);
    new_admin.id=new_admin_id;
    write_admin(new_admin);
    printf("New admin created with ID: %d\n", new_admin_id);
}

int main(){
    // addAdmin();
    print_heading("Good day! Please login to continue");
    print_prelogin_prompt();
    int choice;
    scanf("%d",&choice);
    switch (choice)
    {
    case C_CUSTOMER:
        customer_login();
        break;
    case C_EMPLOYEE:
        employee_login();
        break;
    case C_MANAGER:
        manager_login();
        break;
    case C_ADMIN:
        admin_login();
        break;
    
    default:
        break;
    }
}