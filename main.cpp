#include <stdio.h>
#include <math.h>
#include "equation_solver.h"

enum error {
	NORM,
	FILE_ENDED,
	ERR_FILE_OPEN,
	ERR_FILE_WRITE,
	ERR_FORMAT,
	ERR_BAD_DATA,
	ERR_UNKNOWN
};
	
enum error input_coefficients(FILE *input, struct coefficients *coeffs);
enum error output_roots(FILE *output, struct roots roots);
void print_error(FILE *error, enum error err_code);

int main() {
	struct coefficients coeffs = { NAN, NAN, NAN };
	struct roots roots = { 0, 0, 0 };
	FILE *input, *output, *error;

	if ((output = fopen("output.txt", "a")) == NULL) {
		print_error(stderr, ERR_FILE_OPEN);
		return 1;
	}
	error = output;

	if ((input = fopen("input.txt", "r")) == NULL) {
		print_error(stderr, ERR_FILE_OPEN);
		return 1;
	}

	enum error input_status = NORM, output_status = NORM;

	while (input_status != FILE_ENDED) {
		input_status = input_coefficients(input, &coeffs);
		print_error(error, input_status);

		if (input_status == NORM) {
			solve_quadratic(coeffs, &roots);

			output_status = output_roots(output, roots);
			print_error(error, output_status);
		}
	}

	return 0;
}

void print_error(FILE *error, enum error err_code)
{
	switch (err_code) {
		case NORM:
			return;
		case FILE_ENDED:
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
		default:
			fprintf(error, "[ERROR] an unknown error occured\n");
	}

	if (ferror(error))
		fprintf(stderr, "[ERROR] error writing to an error file\n");

	return;
}

enum error input_coefficients(FILE *input, struct coefficients *coeffs)
{
	int scanned = fscanf(input, "%lf %lf %lf", &coeffs->a, &coeffs->b, &coeffs->c);

	int tmp;
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
