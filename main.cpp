#include "equation_solver.h"
#include "io_handling.h"
#include "logger.h"

#ifdef TEST
#include "tests/test.h"
#endif

int main(int argc, char *argv[]) {
	init_logger();
	add_log_handler({ stderr, DEBUG, true });
	
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
		log_error(ERR_ARG_CNT);
		close_logger();
		return 1;
	} else if (argc > 1) {
		if ((input = fopen(argv[1], "r")) == NULL) {
			log_error(ERR_FILE_OPEN);
			close_logger();
			return 1;
		}

		if (argc == 3 && (output = fopen(argv[2], "w")) == NULL) {
			log_error(ERR_FILE_OPEN);
			close_logger();
			return 1;
		}
	}

	if (output != stdout)
		add_log_handler({ output, WARN, false });

	enum IO_error input_status = NO_IO_ERR, output_status = NO_IO_ERR;

	while (input_status != FILE_ENDED) {
		input_status = input_coefficients(input, &coeffs);

		if (input_status != NO_IO_ERR) {
			log_error(input_status);
		} else {
			solve_quadratic(coeffs, &roots);

			output_status = output_roots(output, roots);
			log_error(output_status);
		}
	}

	close_logger();

	return 0;
}
