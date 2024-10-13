#include "headers/customer.h"
#include "headers/employee.h"
#include "headers/manager.h"
#include "headers/admin.h"
#include "headers/menus.h"
#include "headers/counters.h"
#include<string.h>
#include<stdio.h>

int main(){
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
        employee_login("somename","pass");
        break;
    case C_MANAGER:
        manager_login("somename","pass");
        break;
    case C_ADMIN:
        admin_login("somename","pass");
        break;
    
    default:
        break;
    }
}