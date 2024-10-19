#include "admin.h"
#include "employee.h"
#include "counters.h"
#include "file_utils.h"
#include "menus.h"
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <fcntl.h>

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