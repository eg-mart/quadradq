#include "equation_solver.h"
#include <math.h>
#include <assert.h>
#include <float.h>

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
