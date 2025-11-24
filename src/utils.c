#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <ctype.h>
#include "utils.h"

void clear_input_buffer(void) {
    int c;
    while ((c = getchar()) != '\n' && c != EOF) ;
}

void get_string_input(char *buffer, int max_length) {
    if (fgets(buffer, max_length, stdin) == NULL) {
        buffer[0] = '\0';
        return;
    }
    size_t len = strlen(buffer);
    if (len && buffer[len - 1] == '\n') buffer[len - 1] = '\0';
}

int get_positive_int(void) {
    int v;
    while (1) {
        if (scanf("%d", &v) == 1 && v > 0) {
            clear_input_buffer();
            return v;
        }
        clear_input_buffer();
        printf("Please enter a positive whole number: ");
    }
}

float get_positive_float(void) {
    float v;
    while (1) {
        if (scanf("%f", &v) == 1 && v > 0) {
            clear_input_buffer();
            return v;
        }
        clear_input_buffer();
        printf("Please enter a positive amount: $");
    }
}

void get_current_date(char *buffer) {
    time_t t = time(NULL);
    struct tm tm_info;
    localtime_r(&t, &tm_info);
    strftime(buffer, 11, "%Y-%m-%d", &tm_info);
}

void get_current_time(char *buffer) {
    time_t t = time(NULL);
    struct tm tm_info;
    localtime_r(&t, &tm_info);
    strftime(buffer, 9, "%H:%M:%S", &tm_info);
}

void print_header(const char *title) {
    printf("== %s ==\n", title);
}

void wait_for_enter(void) {
    int c;
    printf("\nPress Enter to continue...");
    while ((c = getchar()) != '\n' && c != EOF) ;
}