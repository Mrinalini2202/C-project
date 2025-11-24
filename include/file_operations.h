#ifndef FILE_OPERATIONS_H
#define FILE_OPERATIONS_H

#include "account_operations.h"

void initialize_bank_files();
void initialize_last_account_number();
int save_account_to_file(BankAccount account);
int get_account(int account_number, BankAccount *account);
int update_account_balance(int account_number, float new_balance);
void record_transaction(int account_number, char type[], float amount, float balance_after);
void display_transaction_history(int account_number);

#endif