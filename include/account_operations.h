#ifndef ACCOUNT_OPERATIONS_H
#define ACCOUNT_OPERATIONS_H

#define ACCOUNTS_FILE "data/accounts.dat"
#define TRANSACTIONS_FILE "data/transactions.dat"

typedef struct {
    int account_number;
    char customer_name[50];
    char address[100];
    char phone[15];
    float balance;
    char creation_date[11];
    int is_active;
} BankAccount;

typedef struct {
    int account_number;
    char transaction_type[20];
    float amount;
    float balance_after;
    char date[11];
    char time[9];
} Transaction;

extern int last_account_number;

int create_new_account(char name[], char address[], char phone[], float initial_deposit);
void process_deposit(int account_number);
void process_withdrawal(int account_number);
void display_account_balance(int account_number);
void display_all_accounts();
int account_exists(int account_number);

#endif