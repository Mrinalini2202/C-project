#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "account_operations.h"
#include "file_operations.h"
#include "utils.h"

void display_main_menu();
void handle_account_creation();
void handle_account_operations();
void handle_transaction_history();

int main() {
     
     printf("\n");
     print_header("Simple Bank Management");
     printf("A minimal banking demo\n\n");

    initialize_bank_files();

    int running = 1;
    int choice;

    while (running) {
        display_main_menu();
        printf("Enter choice (1-6): ");

        if (scanf("%d", &choice) != 1) {
            clear_input_buffer();
            printf("Invalid input. Please enter a number.\n\n");
            continue;
        }

        switch (choice) {
            case 1:
                handle_account_creation();
                break;
            case 2:
                handle_account_operations();
                break;
            case 3:
                handle_transaction_history();
                break;
            case 4:
                display_all_accounts();
                break;
            case 5:
                printf("System maintenance (not implemented)\n");
                wait_for_enter();
                break;
            case 6:
                running = 0;
                printf("Goodbye.\n");
                break;
            default:
                printf("Please choose a number between 1 and 6.\n");
        }

        if (choice != 6) printf("\n");
    }

    return 0;
}

void display_main_menu() {
    printf("\n=== Bank Main Menu ===\n");
    printf("1) Create new account\n");
    printf("2) Account operations\n");
    printf("3) View transaction history\n");
    printf("4) View all accounts\n");
    printf("5) System maintenance\n");
    printf("6) Exit\n");
}

void handle_account_creation() {
    printf("\n");
    print_header("Account Creation");

    char name[50];
    char address[100];
    char phone[15];
    float initial_deposit;

    printf("Customer full name: ");
    get_string_input(name, sizeof(name));

    printf("Address: ");
    get_string_input(address, sizeof(address));

    printf("Phone: ");
    get_string_input(phone, sizeof(phone));

    printf("Initial deposit: $");
    initial_deposit = get_positive_float();

    int new_account_number = create_new_account(name, address, phone, initial_deposit);

    if (new_account_number != -1) {
        printf("Account created. Number: %d, Name: %s, Balance: $%.2f\n",
               new_account_number, name, initial_deposit);
    } else {
        printf("Failed to create account.\n");
    }

    wait_for_enter();
}

void handle_account_operations() {
    int account_number;
    printf("\n");
    print_header("ACCOUNT OPERATIONS");
    
    printf("Enter your account number: ");
    account_number = get_positive_int();
    
    if(!account_exists(account_number)) {
        printf("❌ Account number %d not found!\n", account_number);
        wait_for_enter();
        return;
    }
    
    int operation_choice;
    int operations_active = 1;
    
    while(operations_active) {
        printf("\n╔════════════════════════════════════════════╗\n");
        printf("║          ACCOUNT OPERATIONS MENU          ║\n");
        printf("╠════════════════════════════════════════════╣\n");
        printf("║  1. 💵 Deposit Money                      ║\n");
        printf("║  2. 🏧 Withdraw Money                     ║\n");
        printf("║  3. 📈 Check Balance                      ║\n");
        printf("║  4. 🔄 Back to Main Menu                  ║\n");
        printf("╚════════════════════════════════════════════╝\n");
        printf("\nChoose operation: ");
        
        operation_choice = get_positive_int();
        
        switch(operation_choice) {
            case 1:
                process_deposit(account_number);
                break;
            case 2:
                process_withdrawal(account_number);
                break;
            case 3:
                display_account_balance(account_number);
                break;
            case 4:
                operations_active = 0;
                printf("Returning to main menu...\n");
                break;
            default:
                printf("Invalid choice! Please select 1-4.\n");
        }
        
        if(operation_choice != 4) {
            wait_for_enter();
        }
    }
}

void handle_transaction_history() {
    printf("\n");
    print_header("TRANSACTION HISTORY");
    
    int account_number;
    printf("Enter account number: ");
    account_number = get_positive_int();
    
    if(!account_exists(account_number)) {
        printf("❌ Account number %d not found!\n", account_number);
        wait_for_enter();
        return;
    }
    
    display_transaction_history(account_number);
    wait_for_enter();
}