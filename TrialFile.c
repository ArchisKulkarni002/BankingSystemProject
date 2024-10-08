#include "headers/customer.h"
#include "headers/employee.h"
#include<string.h>
#include<stdio.h>

int main(){
    Customer c;
    // c.id=10;
    // strcpy(c.username, "name1");
    // strcpy(c.password, "pass1");
    // c.balance=11;
    // c.active_status=0;

    // add_new_customer(c);

    c=read_customer(10);
    printf("%s",c.username);
}