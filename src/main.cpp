#include <stdio.h>
#include <math.h>

#include "equation_solver.h"
#include "io_handling.h"
#include "logger.h"

#ifdef TEST
#include "test.h"
#endif

int main(int argc, char *argv[]) {
	init_logger();
	add_log_handler({ stderr, DEBUG, true });

	struct Args args = { false, false, NULL, NULL };
	enum IO_error arg_status = handle_arguments(argc, argv, &args);

	if (arg_status < 0) {
		log_error(arg_status);
		close_logger();
		return 1;
	}

	#ifdef TEST
	if (args.test_mode) {
		run_tests();
		return 0;
	}
	#endif

	FILE *input = stdin, *output = stdout;

	if (args.input_filename != NULL) {
		input = fopen(args.input_filename, "r");
		if (input == NULL) {
			log_error(ERR_FILE_OPEN);
			close_logger();
			return 1;
		}
	}

	if (args.output_filename != NULL) {
		output = fopen(args.output_filename, "w");
		if (output == NULL) {
			log_error(ERR_FILE_OPEN);
			close_logger();
			return 1;
		}
	}

	if (output != stdout)
		add_log_handler({ output, WARN, false });

	enum IO_error input_status = NO_IO_ERR, output_status = NO_IO_ERR;

	struct Coefficients coeffs = { NAN, NAN, NAN };
	struct Roots_info roots = { NAN, NAN, ZERO_ROOTS };

	while (input_status != FILE_ENDED) {
		input_status = input_coefficients(input, &coeffs);

		if (input_status < 0) {
			log_error(input_status);
		} else {
			solve_quadratic(coeffs, &roots);

			output_status = output_roots(output, roots);

			if (output_status < 0)
				log_error(output_status);
		}
	}

	close_logger();
	fclose(output);
	fclose(input);

	return 0;
}
