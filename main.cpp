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

	solve_quadratic(coeffs, &roots);

	switch (roots.n) {
		case 0:
			printf("Решений не найдено.");
			break;
		case 1:
			printf("Найдено 1 решение: %.4lf", roots.x1);
			break;
		case 2:
			printf("Найдено 2 решения: %.4lf %.4lf", roots.x1, roots.x2);
			break;
		case INF_ROOTS:
			printf("Найдено бесконечно много решений.");
			break;
		default:
			fprintf(stderr, "Произошла ошибка!");
			exit(1);
	}

	return 0;
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
	return coeffs.b * coeffs.b - 4 * coeffs.a * coeffs.c;
}

int is_equal(double x, double y)
{
	return fabs(x - y) <= DBL_EPSILON;
}
