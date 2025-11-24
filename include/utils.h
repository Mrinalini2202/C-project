#ifndef UTILS_H
#define UTILS_H

void clear_input_buffer();
void get_string_input(char *buffer, int max_length);
int get_positive_int();
float get_positive_float();
void get_current_date(char *buffer);
void get_current_time(char *buffer);
void print_header(const char *title);
void wait_for_enter();

#endif