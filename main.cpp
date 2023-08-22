#include <stdio.h>
#include <float.h>
#include <math.h>
#include <assert.h>
#include <stdlib.h>

enum solution_stat {
	ERR,
	NO_SOL,
	ONE_SOL,
	TWO_SOL,
	INF_SOL,
};

struct coefficients {
	double a;
	double b;
	double c;
};

struct roots {
	double x1;
	double x2;
	int nroots;
};

int is_equal(double x, double y);
enum solution_stat solve_quadratic(struct coefficients coeffs, struct roots *roots);
enum solution_stat solve_linear(double a, double b, double *x);
double calc_discrim(struct coefficients coeffs);

int main() {
	struct coefficients coeffs = { NAN, NAN, NAN };
	struct roots roots = { NAN, NAN, 0 };

	char buf[64];
	if (fgets(buf, sizeof(buf), stdin)) {
		int n = 0;
		if (sscanf(buf, "%lf %lf %lf %n", &coeffs.a, &coeffs.b, &coeffs.c, &n) != 3 ||
				buf[n] != '\0') {
			fprintf(stderr, "Произошла ошибка ввода");
			exit(1);
		}
	} else {
		fprintf(stderr, "Произошла ошибка ввода");
		exit(1);
	}

	enum solution_stat stat = solve_quadratic(coeffs, &roots);

	switch (stat) {
		case ERR:
			fprintf(stderr, "Произошла ошибка");
			exit(1);
			break;
		case NO_SOL:
			printf("Решений не найдено.");
			break;
		case ONE_SOL:
			printf("Найдено 1 решение: %.4lf", roots.x1);
			break;
		case TWO_SOL:
			printf("Найдено 2 решения: %.4lf %.4lf", roots.x1, roots.x2);
			break;
		case INF_SOL:
			printf("Найдено бесконечно много решений.");
			break;
		default:
			fprintf(stderr, "Произошла ошибка!");
			exit(1);
	}

	return 0;
}

enum solution_stat solve_quadratic(struct coefficients coeffs, struct roots *roots)
{
	if (!(isfinite(coeffs.a) && isfinite(coeffs.b) && isfinite(coeffs.c))) {
		return ERR;
	}

	assert(roots != NULL);
	
	if (is_equal(coeffs.a, 0)) {
		return solve_linear(coeffs.b, coeffs.c, &roots->x1);
	}

	double discmnt = calc_discrim(coeffs);

	if (discmnt < 0) {
		return NO_SOL;
	} else {
		double sqrt_discmnt = sqrt(discmnt);
		roots->x1 = (-coeffs.b - sqrt_discmnt) / (2 * coeffs.a);

		if (discmnt > 0) {
			roots->x2 = (-coeffs.b + sqrt_discmnt) / (2 * coeffs.a);
			return TWO_SOL;
		}

		return ONE_SOL;
	}

	return ERR;
}

enum solution_stat solve_linear(double a, double b, double *x)
{
	if (!(isfinite(a) && isfinite(b))) {
		return ERR;
	}

	assert(x != NULL);

	if (is_equal(a, 0)) {
		if (is_equal(b, 0))
			return INF_SOL;
		else
			return NO_SOL;
	} else {
		*x = -b / a;
		return ONE_SOL;
	}

	return ERR;
}

double calc_discrim(struct coefficients coeffs)
{
	return coeffs.b * coeffs.b - 4 * coeffs.a * coeffs.c;
}

int is_equal(double x, double y)
{
	return fabs(x - y) <= DBL_EPSILON;
}
