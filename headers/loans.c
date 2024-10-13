#include "loans.h"
#include "file_utils.h"
#include <fcntl.h>
#include <stdio.h>

void update_status(int loan_id, int status){
    Loan loan= read_loan(loan_id);
    loan.status=status;
    write_loan(loan.loan_id, loan); 
}
void update_employee(int loan_id, int employee_id){
    Loan loan= read_loan(loan_id);
    loan.assigned_employee_id=employee_id;
    write_loan(loan.loan_id, loan); 
}
void update_amount(int loan_id, int amount){
    Loan loan= read_loan(loan_id);
    loan.amount=amount;
    write_loan(loan.loan_id, loan); 
}
Loan read_loan(int loan_id){
    char filepath[FPATH_SIZE];
    get_loan_file(loan_id, filepath, sizeof(filepath));

    int fd = open_file(filepath, O_RDONLY|O_CREAT);   

    Loan loan;
    read_file(fd, (char*)&loan, sizeof(loan));

    close_file(fd);

    return loan;
}
void write_loan(int loan_id, Loan loan){
    char filepath[FPATH_SIZE];
    get_loan_file(loan_id, filepath, sizeof(filepath));

    int fd = open_file(filepath, O_WRONLY|O_CREAT);   

    write_file(fd, (char*)&loan, sizeof(loan));

    close_file(fd);
}
void get_loan_file(int id, char* filepath, int size){
    snprintf(filepath, size, "loans/%d", id);
}