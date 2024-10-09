#include "headers/customer.h"
#include "headers/employee.h"
#include "headers/transactions.h"
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

    transfer_funds(10, 11, 50);
    print_transaction_history(10);
    print_transaction_history(11);
    printf("10 balance: %f\n", view_balance(10));
    printf("11 balance: %f\n", view_balance(11));
}