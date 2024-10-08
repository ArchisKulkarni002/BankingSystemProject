
#ifndef CUSTOMER_H
#define CUSTOMER_H

typedef struct {
    int id;
    char username[50];
    char password[50];
    float balance;
    int active_status;
}Customer;

#define FPATH_SIZE 500

void customer_login(char* username, char* password);
float view_balance(int customer_id);
void deposit_money(int customer_id, float amount);
void withdraw_money(int customer_id, float amount);
void transfer_funds(int sender_id, int receiver_id, float amount);
void apply_loan(int customer_id, float loan_amount);
void view_transaction_history(int customer_id);
void submit_feedback(int customer_id, char* feedback);
Customer read_customer(int id);
void write_customer(Customer customer);
void get_file_path(int id, char* filepath, int size);

#endif // CUSTOMER_H