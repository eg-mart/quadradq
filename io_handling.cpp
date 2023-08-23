#include "io_handling.h"

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

void print_error(FILE *error, enum error err_code)
{
	assert(error != NULL);
	
	switch (err_code) {
		case NO_ERR:
			return;
		case FILE_ENDED:
			return;
		case ERR_NO_ARGS:
			return;
		case ERR_FILE_OPEN:
			fprintf(error, "[ERROR] error opening a file\n");
			break;
		case ERR_FILE_WRITE:
			fprintf(error, "[ERROR] error writing to a file\n");
			break;
		case ERR_FORMAT:
			fprintf(error, "[ERROR] wrong input format\n");
			break;
		case ERR_BAD_DATA:
			fprintf(error, "[ERROR] bad input data\n");
			break;
		case ERR_ARG_CNT:
			fprintf(error, "[ERROR] Wrong arguments. Usage: quadradq input [output]\n");
			break;
		case ERR_UNKNOWN:
		default:
			fprintf(error, "[ERROR] an unknown error occured\n");
	}

	if (ferror(error))
		fprintf(stderr, "[ERROR] error writing to an error file\n");

	return;
}

enum error input_coefficients(FILE *input, struct Coefficients *coeffs)
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

	return NO_ERR;
}

enum error output_roots(FILE *output, struct Roots_info roots)
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

	return NO_ERR;
}
