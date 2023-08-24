#include "io_handling.h"
#include "logger.h"

void handle_arguments(int argc, char *argv[], bool *test_mode)
{
	assert(argv != NULL);
	assert(test_mode != NULL);

	if (argc < 2)
		return;

	#ifdef TEST
	if (strcmp(argv[1], "--test") == 0) {
		*test_mode = true;
	}
	#endif
}

void log_error(enum IO_error err_code)
{
	switch (err_code) {
		case NO_IO_ERR:
			return;
		case FILE_ENDED:
			return;
		case ERR_NO_ARGS:
			return;
		case ERR_FILE_OPEN:
			log_message(ERROR, "error opening a file\n");
			break;
		case ERR_FILE_WRITE:
			log_message(ERROR, "error writing to a file\n");
			break;
		case ERR_FORMAT:
			log_message(WARN, "wrong input format\n");
			break;
		case ERR_BAD_DATA:
			log_message(WARN, "bad input data\n");
			break;
		case ERR_ARG_CNT:
			log_message(ERROR, "Wrong arguments. Usage: quadradq input [output]\n");
			break;
		case ERR_UNKNOWN:
		default:
			log_message(ERROR, "[ERROR] an unknown error occured\n");
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
	assert(0 == 1);

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
