#include "calc.h"


int main(int argc, char** argv) {
	int expr_count = 0;
	int key_index = 0;
	

	if (valid_input(argc, argv, &expr_count, &key_index) == -1) {
		return EXIT_FAILURE;
	}

	int key = atoi(argv[key_index + 1]);
	int* results = process_expressions(argv, argc, &expr_count, &key_index);
	char* asci_string = asci_result(results, expr_count, key);
	print_result(results, expr_count, asci_string);
	free(results);
	free(asci_string);
	
	return EXIT_SUCCESS;
}

