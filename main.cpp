#include <stdio.h>
#include <assert.h>
#include <math.h>
#include "equation_solver.h"

enum error {
	NORM,
	FILE_ENDED,
	ERR_FILE_OPEN,
	ERR_FILE_WRITE,
	ERR_FORMAT,
	ERR_BAD_DATA,
	ERR_UNKNOWN,
	ERR_ARG_CNT,
	ERR_NO_ARGS
};

enum error input_coefficients(FILE *input, struct coefficients *coeffs);
enum error output_roots(FILE *output, struct roots roots);
void print_error(FILE *error, enum error err_code);
enum error handle_arguments(int argc, char *argv[], FILE **input, FILE **output);

int main(int argc, char *argv[]) {
	struct coefficients coeffs = { NAN, NAN, NAN };
	struct roots roots = { 0, 0, ZERO_ROOTS };
	FILE *input = stdin, *output = stdout;

	enum error arg_status = handle_arguments(argc, argv, &input, &output);
	print_error(stderr, arg_status);

	if (arg_status == ERR_NO_ARGS) {
		input = stdin;
		output = stdout;
	} else if (arg_status != NORM) {
		return 1;
	}

	enum error input_status = NORM, output_status = NORM;

	while (input_status != FILE_ENDED) {
		input_status = input_coefficients(input, &coeffs);
		print_error(output, input_status);

		if (input_status == NORM) {
			solve_quadratic(coeffs, &roots);

			output_status = output_roots(output, roots);
			print_error(output, output_status);
		}
	}

	return 0;
}

enum error handle_arguments(int argc, char *argv[], FILE **input, FILE **output)
{
	assert(input != NULL);
	assert(output != NULL);
	assert(argv != NULL);
	assert(input != output);

	if (argc == 1)
		return ERR_NO_ARGS;

	if (argc != 3)
		return ERR_ARG_CNT;

	if ((*input = fopen(argv[1], "r")) == NULL)
		return ERR_FILE_OPEN;

	if ((*output = fopen(argv[2], "w")) == NULL)
		return ERR_FILE_OPEN;

	return NORM;
}

void print_error(FILE *error, enum error err_code)
{
	assert(error != NULL);
	
	switch (err_code) {
		case NORM:
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
		case ERR_UNKNOWN:
			fprintf(error, "[ERROR] an unknown error occured\n");
			break;
		case ERR_ARG_CNT:
			fprintf(error, "[ERROR] Wrong arguments. Usage: quadradq input output\n");
			break;
		default:
			fprintf(error, "[ERROR] an unknown error occured\n");
	}

	if (ferror(error))
		fprintf(stderr, "[ERROR] error writing to an error file\n");

	return;
}

enum error input_coefficients(FILE *input, struct coefficients *coeffs)
{
	assert(input != NULL);
	
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

	return NORM;
}

enum error output_roots(FILE *output, struct roots roots)
{
	assert(output != NULL);

	if (is_equal(roots.x1, 0))
		roots.x1 = 0;

	if (is_equal(roots.x2, 0))
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

	return NORM;
}
