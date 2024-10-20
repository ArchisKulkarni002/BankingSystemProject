#include "employee.h"
#ifndef ADMIN_H
#define ADMIN_H

typedef struct{
    int id;
    char username[50];
    char password[50];
    int active_status;
}Admin;

int add_new_employee(Employee new_employee);
void modify_user_details(int user_id, char* new_username, char* new_password);
void manage_user_roles(int user_id, char* new_role);
Admin read_admin(int id);
void write_admin(Admin admin);
void get_admin_file(int id, char* filepath, int size);

#endif // ADMIN_H