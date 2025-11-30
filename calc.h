#ifndef CALCULATOR_H
#define CALCULATOR_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>


int calc_expressions(int left_operand, char op,int right_operand);
int* process_expressions(char** argv, int argc, int* count, int* key_index);
char* asci_result(int* result, int count, int key);
void print_result(int* result, int count, char* asci_string);
int valid_op(char op);
int valid_input(int argc, char** argv,int* expr_count,int* key_index);
int is_number(const char* str);
#endif 
