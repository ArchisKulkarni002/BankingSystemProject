#include "menus.h"
#include "file_utils.h"
#include<stdio.h>
#include <ctype.h>

void print_heading(char* heading){
    // make the heading to upper case
    int counter=0;
    printf("|  ");
    for (int i = 0; heading[i] != '\0'; i++) {
        printf("%c", toupper((unsigned char)heading[i]));
        counter++;
    }
    
    printf("  |\n");
    print_underline(counter+6);
}

void print_subheading(char* heading){
    printf("|  %s  |\n", heading);
}


void print_underline(int counter){
    for (int i = 0; i<counter; i++) {
        printf("-");
    }
    
    printf("\n\n");
}

// LOGIN SCREENS
void print_prelogin_prompt(){
    print_subheading("Who are you logging in as?");
    printf("1.Customer\n");
    printf("2.Employee\n");
    printf("3.Manager\n");
    printf("4.Admin\n");
    printf("Enter your choice:");
}           
void print_login_success(char* role){
    printf("Logged in as %s.\n", role);
}
void print_login_failure(){
    printf("Log in failed, please try again.\n");
}          
void print_logout_message(){
    printf("Logged out successfully.\n");
}

// ROLE-WISE MENUS
void print_customer_menu(){
    print_heading("Customer Menu");
    printf("1.View Account Balance \n");
    printf("2.Deposit Money \n");
    printf("3.Withdrawl Money \n");
    printf("4.Transfer Funds \n");
    printf("5.Apply for a Loan  \n");
    printf("6.Change Password   \n");
    printf("7.Adding Feedback    \n");
    printf("8.View Transaction History    \n");
    printf("9.Logout\n");
    printf("10.Exit\n");
    printf("Enter your choice: ");
}          
void print_employee_menu(){
    print_heading("Employee Menu");
    printf("1.Add New Customer  \n");
    printf("2.Modify Customer Details \n");
    printf("3.Process Loan Applications \n");
    printf("4.Approve/Reject Loans \n");
    printf("5.View Assigned Loan Applications  \n");
    printf("6.View Customer Transactions   \n");
    printf("7.Change Password    \n");
    printf("8.Logout\n");
    printf("9.Exit\n");
}          
void print_manager_menu(){
    print_heading("Manager Menu");
    printf("1.Activate/Deactivate Customer Accounts  \n");
    printf("2.Assign Loan Application Processes to Employees \n");
    printf("3.Review Customer Feedback \n");
    printf("4.Change Password    \n");
    printf("5.Logout\n");
    printf("6.Exit\n");
}           
void print_admin_menu(){
    print_heading("Admin Menu");
    printf("1.Add New Bank Employee\n");
    printf("2.Modify Customer/Employee Details \n");
    printf("3.Manage User Roles  \n");
    printf("4.Change Password    \n");
    printf("5.Logout\n");
    printf("6.Exit\n");
}             


void log_info(char* info){
    if (LOGGING==1)
    {
        printf("LOG: %s\n", info);
    }
    
}