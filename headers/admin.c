#include "admin.h"
#include "employee.h"
#include "file_utils.h"
#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>

void admin_login(char* username, char* password){
    
}
void add_new_employee(Employee new_employee){
    char filepath[FPATH_SIZE];
    get_customer_file(new_employee.id, filepath, sizeof(filepath));

    if (access(filepath, F_OK)==0){
        perror("The employee with that id already exists");
    }else{
        write_employee(new_employee);
    }
}
void modify_user_details(int user_id, char* new_username, char* new_password){
    
}
void manage_user_roles(int user_id, char* new_role){

}

void get_admin_file(int id, char* filepath, int size){
    snprintf(filepath, size, "admin/%d", id);
}