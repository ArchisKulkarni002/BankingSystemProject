#ifndef MENUS_H
#define MENUS_H

void print_heading(char* heading);
void print_subheading(char* heading);
void print_underline(int counter);
void print_status(char* message);

void print_prelogin_prompt();           
void print_login_success(char* role);
void print_login_failure();          
void print_logout_message();

void print_customer_menu();          
void print_employee_menu();          
void print_manager_menu();           
void print_admin_menu();            

void log_info(char* info);


#endif // MENUS_H