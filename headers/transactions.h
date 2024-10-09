#ifndef TRANSACTIONS_H
#define TRANSACTIONS_H
#define MSG_LEN 100

typedef struct {
    int type;
    float amount;
    int sender_id;
    int receiver_id;
}Transaction;

void record_transaction(Transaction transaction);
void print_transaction_history(int customer_id);
void get_transactions_file(int id, char* filepath, int size);

#endif // TRANSACTIONS_H