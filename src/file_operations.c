#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "file_operations.h"
#include "utils.h"

void initialize_bank_files(void) {
    FILE *f = fopen(ACCOUNTS_FILE, "ab");
    if (f) fclose(f);
    f = fopen(TRANSACTIONS_FILE, "ab");
    if (f) fclose(f);
    initialize_last_account_number();
}

void initialize_last_account_number(void) {
    FILE *f = fopen(ACCOUNTS_FILE, "rb");
    if (!f) return;

    BankAccount a;
    int max_no = 1000;
    while (fread(&a, sizeof a, 1, f) == 1) {
        if (a.account_number > max_no) max_no = a.account_number;
    }
    fclose(f);

    extern int last_account_number;
    last_account_number = max_no;
}

int save_account_to_file(BankAccount account) {
    FILE *f = fopen(ACCOUNTS_FILE, "ab");
    if (!f) return 0;
    int res = fwrite(&account, sizeof account, 1, f) == 1;
    fclose(f);
    return res;
}

int get_account(int account_number, BankAccount *account) {
    FILE *f = fopen(ACCOUNTS_FILE, "rb");
    if (!f) return 0;
    BankAccount tmp;
    while (fread(&tmp, sizeof tmp, 1, f) == 1) {
        if (tmp.account_number == account_number && tmp.is_active) {
            *account = tmp;
            fclose(f);
            return 1;
        }
    }
    fclose(f);
    return 0;
}

int update_account_balance(int account_number, float new_balance) {
    FILE *f = fopen(ACCOUNTS_FILE, "rb+");
    if (!f) return 0;
    BankAccount tmp;
    long pos = -1;
    while (fread(&tmp, sizeof tmp, 1, f) == 1) {
        if (tmp.account_number == account_number) {
            pos = ftell(f) - (long)sizeof tmp;
            break;
        }
    }
    if (pos < 0) { fclose(f); return 0; }
    tmp.balance = new_balance;
    fseek(f, pos, SEEK_SET);
    int ok = fwrite(&tmp, sizeof tmp, 1, f) == 1;
    fclose(f);
    return ok;
}

void record_transaction(int account_number, char type[], float amount, float balance_after) {
    FILE *f = fopen(TRANSACTIONS_FILE, "ab");
    if (!f) return;
    Transaction t;
    t.account_number = account_number;
    strcpy(t.transaction_type, type);
    t.amount = amount;
    t.balance_after = balance_after;
    get_current_date(t.date);
    get_current_time(t.time);
    fwrite(&t, sizeof t, 1, f);
    fclose(f);
}

void display_transaction_history(int account_number) {
    FILE *f = fopen(TRANSACTIONS_FILE, "rb");
    if (!f) { printf("No transaction history available.\n"); return; }
    Transaction t;
    int count = 0;
    printf("\nTransactions for %d:\n", account_number);
    printf("Date Time Type Amount Balance\n");
    while (fread(&t, sizeof t, 1, f) == 1) {
        if (t.account_number == account_number) {
            printf("%s %s %s $%.2f $%.2f\n", t.date, t.time, t.transaction_type, t.amount, t.balance_after);
            count++;
        }
    }
    fclose(f);
    if (count == 0) printf("No transactions found for this account.\n");
    else printf("Total transactions: %d\n", count);
}