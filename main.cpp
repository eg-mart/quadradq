#include "equation_solver.h"
#include "io_handling.h"

#ifdef TEST
#include "tests/test.h"
#endif

int main(int argc, char *argv[]) {
	struct Coefficients coeffs = { NAN, NAN, NAN };
	struct Roots_info roots = { NAN, NAN, ZERO_ROOTS };

	bool test_mode = false;
	handle_arguments(argc, argv, &test_mode);

	#ifdef TEST
	if (test_mode) {
		run_tests();
		return 0;
	}
	#endif

	FILE *input = stdin, *output = stdout;

	if (argc > 3) {
		print_error(stderr, ERR_ARG_CNT);
		return 1;
	} else if (argc > 1) {
		if ((input = fopen(argv[1], "r")) == NULL) {
			print_error(stderr, ERR_FILE_OPEN);
			return 1;
		}

		if (argc == 3 && (output = fopen(argv[2], "w")) == NULL) {
			print_error(stderr, ERR_FILE_OPEN);
			return 1;
		}
	}

	enum error input_status = NO_ERR, output_status = NO_ERR;

	while (input_status != FILE_ENDED) {
		input_status = input_coefficients(input, &coeffs);

		if (input_status != NO_ERR) {
			print_error(output, input_status);
		} else {
			solve_quadratic(coeffs, &roots);

			output_status = output_roots(output, roots);
			print_error(output, output_status);
		}
	}

	return 0;
}
