#ifndef LOANS_H
#define LOANS_H

typedef struct {
    int loan_id;
    int customer_id;
    float amount;
    int assigned_employee_id;
    int status;  // "1. Pending", "2. Approved", "3. Rejected"
}Loan;

void update_status(int loan_id, int status);
void update_employee(int loan_id, int employee_id);
void update_amount(int loan_id, int amount);
Loan read_loan(int loan_id);
void write_loan(int loan_id, Loan loan);
void get_loan_file(int id, char* filepath, int size);

#endif // LOANS_H