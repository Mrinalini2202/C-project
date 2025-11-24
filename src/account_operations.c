#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "account_operations.h"
#include "file_operations.h"
#include "utils.h"

int last_account_number = 1000;

int create_new_account(char name[], char address[], char phone[], float initial_deposit) {
    
    int new_account_number = ++last_account_number;

    BankAccount acct;
    strcpy(acct.customer_name, name);
    strcpy(acct.address, address);
    strcpy(acct.phone, phone);
    acct.account_number = new_account_number;
    acct.balance = initial_deposit;
    acct.is_active = 1;
    get_current_date(acct.creation_date);

    if (save_account_to_file(acct)) {
        record_transaction(new_account_number, "INITIAL_DEPOSIT", initial_deposit, acct.balance);
        return new_account_number;
    }
    return -1;
}

void process_deposit(int account_number) {
    printf("\nDeposit\n");
    printf("Amount: $");
    float amount = get_positive_float();
    if (amount <= 0) {
        printf("Amount must be positive.\n");
        return;
    }

    BankAccount acct;
    if (!get_account(account_number, &acct)) {
        printf("Account %d not found.\n", account_number);
        return;
    }

    acct.balance = acct.balance + amount;
    if (update_account_balance(account_number, acct.balance)) {
        record_transaction(account_number, "DEPOSIT", amount, acct.balance);
        printf("Deposited $%.2f. New balance: $%.2f\n", amount, acct.balance);
    } else {
        printf("Could not save new balance.\n");
    }
}

void process_withdrawal(int account_number) {
    printf("\nWithdraw\n");
    printf("Amount: $");
    float amount = get_positive_float();
    if (amount <= 0) {
        printf("Amount must be positive.\n");
        return;
    }

    BankAccount acct;
    if (!get_account(account_number, &acct)) {
        printf("Account %d not found.\n", account_number);
        return;
    }

    if (amount > acct.balance) {
        printf("Insufficient funds.\n");
        return;
    }

    acct.balance = acct.balance - amount;
    if (update_account_balance(account_number, acct.balance)) {
        record_transaction(account_number, "WITHDRAWAL", amount, acct.balance);
        printf("Withdrew $%.2f. New balance: $%.2f\n", amount, acct.balance);
    } else {
        printf("Could not save new balance.\n");
    }
}

void display_account_balance(int account_number) {
    BankAccount acct;
    if (!get_account(account_number, &acct)) {
        printf("Account %d not found.\n", account_number);
        return;
    }

    printf("Account Number: %d\n", acct.account_number);
    printf("Customer: %s\n", acct.customer_name);
    printf("Balance: $%.2f\n", acct.balance);
    printf("Active: %d\n", acct.is_active);
    printf("Created on: %s\n", acct.creation_date);
}

void display_all_accounts(void) {
    FILE *f = fopen(ACCOUNTS_FILE, "rb");
    if (!f) {
        printf("No accounts found.\n");
        return;
    }

    BankAccount a;
    int i = 0;
    float sum = 0.0f;
    printf("\nAccNo  Name               Phone       Bal   Active\n");
    while (fread(&a, sizeof a, 1, f) == 1) {
        printf("%5d  %-17s  %-10s  %6.2f  %d\n",
               a.account_number, a.customer_name, a.phone, a.balance, a.is_active);
        i++;
        sum += a.balance;
    }
    fclose(f);
    printf("\nTotal accounts: %d\nTotal money: $%.2f\n", i, sum);
}

int account_exists(int account_number) {
    BankAccount account;
    return get_account(account_number, &account);
}