#include <stdio.h>
#include <float.h>
#include <math.h>
#include <assert.h>
#include <stdlib.h>

enum error {
	NORM,
	FILE_ENDED,
	ERR_FILE_OPEN,
	ERR_FILE_WRITE,
	ERR_FORMAT,
	ERR_UNKNOWN
};
	
struct coefficients {
	double a;
	double b;
	double c;
};

const int INF_ROOTS = -1;

struct roots {
	double x1;
	double x2;
	int n;
};

int is_equal(double x, double y);
void solve_quadratic(struct coefficients coeffs, struct roots *roots);
void solve_linear(double a, double b, struct roots *roots);
double calc_discrim(struct coefficients coeffs);
enum error input_coefficients(FILE *input, struct coefficients *coeffs);
enum error output_roots(FILE *output, struct roots roots);
int print_error(FILE *error, enum error err_code);

int main() {
	struct coefficients coeffs = { NAN, NAN, NAN };
	struct roots roots = { NAN, NAN, 0 };
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

int print_error(FILE *error, enum error err_code)
{
	switch (err_code) {
		case NORM:
			return 0;
		case FILE_ENDED:
			return 0;
		case ERR_FILE_OPEN:
			fprintf(error, "[ERROR] error opening a file\n");
			break;
		case ERR_FILE_WRITE:
			fprintf(error, "[ERROR] error writing to a file\n");
			break;
		case ERR_FORMAT:
			fprintf(error, "[ERROR] wrong input format\n");
			break;
		case ERR_UNKNOWN:
			fprintf(error, "[ERROR] an unknown error occured\n");
			break;
		default:
			fprintf(error, "[ERROR] an unknown error occured\n");
	}

	if (ferror(error))
		fprintf(stderr, "[ERROR] error writing to an error file\n");

	return 1;
}

enum error input_coefficients(FILE *input, struct coefficients *coeffs)
{
	int scanned = fscanf(input, "%lf %lf %lf ", &coeffs->a, &coeffs->b, &coeffs->c);

	int tmp = '\n';
	if (scanned != 3 && scanned != EOF) {
		while ((tmp = getc(input)) != '\n' && tmp != EOF)
			;
		return ERR_FORMAT;
	}

	if (scanned == EOF || tmp == EOF) {
		return FILE_ENDED;
	}

	return NORM;
}

enum error output_roots(FILE *output, struct roots roots)
{
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

void solve_quadratic(struct coefficients coeffs, struct roots *roots)
{
	assert(isfinite(coeffs.a));
	assert(isfinite(coeffs.b));
	assert(isfinite(coeffs.c));
	assert(roots != NULL);
	
	if (is_equal(coeffs.a, 0)) {
		solve_linear(coeffs.b, coeffs.c, roots);
		return;
	}

	double discmnt = calc_discrim(coeffs);

	if (discmnt < 0) {
		roots->n = 0;
		return;
	}

	double sqrt_discmnt = sqrt(discmnt);
	roots->x1 = (-coeffs.b - sqrt_discmnt) / (2 * coeffs.a);

	if (discmnt > 0) {
		roots->x2 = (-coeffs.b + sqrt_discmnt) / (2 * coeffs.a);
		roots->n = 2;
		return;
	}

	roots->n = 1;
	return;
}

void solve_linear(double a, double b, struct roots *roots)
{
	assert(isfinite(a));
	assert(isfinite(b));
	assert(roots != NULL);

	if (is_equal(a, 0)) {
		if (is_equal(b, 0)) {
			roots->n = INF_ROOTS;
			return;
		}
		roots->n = 0;
		return;
	}

	roots->n = 1;
	roots->x1 = -b / a;

	return;
}

double calc_discrim(struct coefficients coeffs)
{
	assert(isfinite(coeffs.a));
	assert(isfinite(coeffs.b));
	assert(isfinite(coeffs.c));

	return coeffs.b * coeffs.b - 4 * coeffs.a * coeffs.c;
}

int is_equal(double x, double y)
{
	assert(isfinite(x));
	assert(isfinite(y));

	return fabs(x - y) <= DBL_EPSILON;
}
