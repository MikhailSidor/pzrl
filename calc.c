#include "calc.h"

int valid_op(char op) {
	return (op == '+' || op == '-' || op == '*' || op == '%');
}
int is_number(const char* str) {
	if (str == NULL || *str == '\0')
		return 0;
	
	if (*str == '-' && strlen(str) > 1) str++;

	while(*str) {
		if(!isdigit(*str))
			return 0;
		str++;
	}
	return 1;
}



int calc_expressions(int left_operand, char op, int right_operand) {
	switch(op) {
		case '+': return left_operand + right_operand;
		case '-': return left_operand - right_operand;
		case '*': return left_operand * right_operand;
		case '%':
			if (right_operand == 0) {
				fprintf(stderr, "Err\n");
				exit(EXIT_FAILURE);
			
			} else {
				return left_operand % right_operand;
			}
		default:
			fprintf(stderr, "Err, unknown operator\n");
			exit(EXIT_FAILURE); 
	}
}


int valid_input(int argc, char** argv,int* expr_count, int* key_index) {
	*key_index = -1;
	for (int i = 1; i < argc; i++) {
		if (strcmp(argv[i], "-k") == 0)  {
			*key_index = i;
			break;
		}
	}
	
	if (*key_index == -1) {
		fprintf(stderr, "-k not found!\n");
		return -1;
	}
	
	if (*key_index == argc - 1) {
		fprintf(stderr, "no key after -k!\n");
		return -1;
	}
	if (!is_number(argv[*key_index + 1])) {
		fprintf(stderr, "Key must be a number\n");
		return -1;
	}

	*expr_count = (*key_index + 1) / 3;
	if ((*key_index - 1) % 3 != 0 || *expr_count == 0) {
		fprintf(stderr, "invalid quantity of arguments\n");
		return -1;
	}
	for (int i = 1; i < *key_index; i += 3) {
		if (!is_number(argv[i])) {
			fprintf(stderr, "Left operand must be a number\n");
			return -1;
		}
		
		if (strlen(argv[i + 1]) != 1 || !valid_op(argv[i + 1][0])) {
			fprintf(stderr, "Invalid operator\n");
			return -1;
		}
		
		if (!is_number(argv[i + 2])) {
			fprintf(stderr, "Right operand must be a number\n");
			return -1;
		}
	}
	return 0;
}

int* process_expressions(char** argv, int argc, int* count, int* key_index) {
	*count = 0;
	for (int i = 1; i < argc; i++) {
		if (strcmp(argv[i], "-k") == 0) {
			*key_index = i;
			break;
		}
	}

	*count = (*key_index - 1) / 3;

	int* results = (int*)malloc(*count * sizeof(int));
	if (!results) {
		fprintf(stderr, "Memory allocation err\n");
		exit(EXIT_FAILURE);
	}

	for (int i = 0; i < *count; i++) {
		int arg_index = 1 + i * 3;
		int left_op = atoi(argv[arg_index]);
		int op = argv[arg_index + 1][0];
		int right_op = atoi(argv[arg_index + 2]);
	
		results[i] = calc_expressions(left_op, op, right_op);
	}
	
	return results;
}



char* asci_result(int* results, int count, int key) {
	char* asci_string = (char*)malloc((count + 1) * sizeof(char));
	if (!asci_string) {
		fprintf(stderr, "Memory allocation err\n");
		return NULL;
	}

	for (int i = 0; i < count; i++) {	
		int ascii_value = results[i] - key;
		if (ascii_value < 0 || ascii_value > 127) {
			fprintf(stderr, "Out of ascii range\n");
		} else {
			asci_string[i] = (char)ascii_value;
		}
	}
	asci_string[count] = '\0';

	return asci_string;
}
		


void print_result(int* result, int count, char* asci_string) {
	for (int i = 0; i < count; i++) {
		printf("Answer №%d: %d\n", i + 1, result[i]);
	}
	printf("Decrypted string: %s\n", asci_string);
}














