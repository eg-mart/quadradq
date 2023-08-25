#include <string.h>
#include <stdio.h>
#include <math.h>

#include "logger.h"
#include "assert.h"
#include "equation_solver.h"
#include "io_handling.h"

enum IO_error handle_arguments(int argc, char *argv[], struct Args *args)
{
	assert(argv != NULL);
	assert(args != NULL);

	if (argc < 2)
		return NO_ARGS;

	char c = '\0';
	while (--argc > 0 && (*++argv)[0] == '-') {
		#ifdef TEST
		if (strcmp(*argv, "--test") == 0) {
			args->test_mode = true;
			continue;
		}
		#endif

		bool flags_ended = false;
		while ((c = *++argv[0]) && !flags_ended)
			switch (c) {
				case 'm':
					args->use_complex = true;
					break;
				case 'i':
					if (argc < 2 || *++argv[0] != '\0' || (*++argv)[0] == '-')
						return ERR_NO_FILENAME;
					args->input_filename = argv[0];
					argc--;
					flags_ended = true;
					break;
				case 'o':
					if (argc < 2 || *++argv[0] != '\0' || (*++argv)[0] == '-')
						return ERR_NO_FILENAME;
					args->output_filename = argv[0];
					argc--;
					flags_ended = true;
					break;
				default:
					return ERR_WRONG_ARG;
			}
	}

	if (argc > 0)
		return ERR_WRONG_ARG;
	return NO_IO_ERR;
}

void log_error(enum IO_error err_code)
{
	switch (err_code) {
		case ERR_FILE_OPEN:
			log_message(ERROR, "Error opening a file\n");
			break;
		case ERR_FILE_WRITE:
			log_message(ERROR, "Error writing to a file\n");
			break;
		case ERR_FORMAT:
			log_message(WARN, "wrong input format\n");
			break;
		case ERR_BAD_DATA:
			log_message(WARN, "Bad input data\n");
			break;
		case ERR_WRONG_ARG:
			log_message(ERROR, "Wrong arguments. Usage: quadradq input [output]\n");
			break;
		case ERR_NO_FILENAME:
			log_message(ERROR, "-i and -o flags require a filename after them.\n");
			break;
		case ERR_UNKNOWN:
		default:
			log_message(ERROR, "An unknown error occured\n");
	}
}

enum IO_error input_coefficients(FILE *input, struct Coefficients *coeffs)
{
	assert(input != NULL);
	assert(coeffs != NULL);
	
	int scanned = fscanf(input, "%lf %lf %lf", &coeffs->a, &coeffs->b, &coeffs->c);

	int tmp = 0;
	int format_error = 0;

	while ((tmp = getc(input)) != '\n' && tmp != EOF) {
		if (tmp != ' ')
			format_error = 1;
	}

	if ((scanned != 3 && scanned != EOF) || format_error)
		return ERR_FORMAT;

	if (scanned == EOF || tmp == EOF)
		return FILE_ENDED;

	if (!(isfinite(coeffs->a) && isfinite(coeffs->b) && isfinite(coeffs->c)))
		return ERR_BAD_DATA;

	return NO_IO_ERR;
}

enum IO_error output_roots(FILE *output, struct Roots_info roots)
{
	assert(output != NULL);

	if (isfinite(roots.x1) && is_equal(roots.x1, 0))
		roots.x1 = 0;

	if (isfinite(roots.x2) && is_equal(roots.x2, 0))
		roots.x2 = 0;

	switch (roots.n) {
		case 0:
			fprintf(output, "no roots\n");
			break;
		case 1:
			fprintf(output, "%lg\n", roots.x1);
			break;
		case 2:
			fprintf(output, "%lg %lg\n", roots.x1, roots.x2);
			break;
		case INF_ROOTS:
			fprintf(output, "infinite roots\n");
			break;
		default:
			return ERR_UNKNOWN;
	}

	if (ferror(output))
		return ERR_FILE_WRITE;

	return NO_IO_ERR;
}
