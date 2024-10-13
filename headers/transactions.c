#include "transactions.h"
#include "file_utils.h"
#include<fcntl.h>
#include<stdio.h>

void record_transaction(Transaction transaction){
    // transaction can either be to same account(deposit or withdrawl)
    // or to different accounts(transfer). 

    if(transaction.sender_id==transaction.receiver_id){
        char filepath1[FPATH_SIZE];
        get_transactions_file(transaction.receiver_id, filepath1, sizeof(filepath1));

        int fd1 = open_file(filepath1, O_WRONLY | O_APPEND | O_CREAT);

        write_file(fd1, (char*)&transaction, sizeof(Transaction));
        close_file(fd1);
    }

    else{
        // update receiver record
        char filepath1[FPATH_SIZE];
        get_transactions_file(transaction.receiver_id, filepath1, sizeof(filepath1));

        int fd1 = open_file(filepath1, O_WRONLY | O_APPEND | O_CREAT);

        transaction.type=1;
        write_file(fd1, (char*)&transaction, sizeof(Transaction));

        // update sender record
        char filepath2[FPATH_SIZE];
        get_transactions_file(transaction.sender_id, filepath2, sizeof(filepath2));

        int fd2 = open_file(filepath2, O_WRONLY | O_APPEND | O_CREAT);

        transaction.type=-1;
        write_file(fd2, (char*)&transaction, sizeof(Transaction));

        close_file(fd1);
        close_file(fd2);
    }

    
}
void print_transaction_history(int customer_id){
    Transaction transaction;
    int bytesRead;
    char filepath2[FPATH_SIZE];
    get_transactions_file(customer_id, filepath2, sizeof(filepath2));
    int fd = open_file(filepath2, O_RDONLY|O_CREAT);

    printf("Printing transactions history for account %d\n", customer_id);

    while ((bytesRead = read(fd, &transaction, sizeof(Transaction))) > 0) {
        // Check if we read the correct number of bytes
        if (bytesRead != sizeof(Transaction)) {
            fprintf(stderr, "Error reading transaction\n");
            break;
        }
        if (transaction.sender_id==transaction.receiver_id){
            if (transaction.type==1){
                printf("Deposited %f rupees.\n", transaction.amount);
            }else if (transaction.type==-1){
                printf("Withdrawn %f rupees.\n", transaction.amount);
            }          
        }else{
            if (transaction.type==-1){
                printf("Sent %f rupees to account number %d.\n", transaction.amount, transaction.receiver_id);
            }else if (transaction.type==1){
                printf("Received %f rupees from account number %d.\n", transaction.amount, transaction.sender_id);
            }
        }
        
        
    }

    close_file(fd);
}

void get_transactions_file(int id, char* filepath, int size){
    snprintf(filepath, size, "transactions/%d", id);
}