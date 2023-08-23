#include "equation_solver.h"

const double PRECISION = 1e-6;

void solve_quadratic(struct Coefficients coeffs, struct Roots_info *roots)
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
		roots->n = ZERO_ROOTS;
		return;
	}

	double sqrt_discmnt = sqrt(discmnt);
	roots->x1 = (-coeffs.b - sqrt_discmnt) / (2 * coeffs.a);
	roots->x1 = round(roots->x1 / PRECISION) * PRECISION;

	if (discmnt > 0) {
		roots->x2 = (-coeffs.b + sqrt_discmnt) / (2 * coeffs.a);
		roots->x2 = round(roots->x1 / PRECISION) * PRECISION;
		roots->n = TWO_ROOTS;
		return;
	}

	roots->n = ONE_ROOT;
	return;
}

void solve_linear(double a, double b, struct Roots_info *roots)
{
	assert(isfinite(a));
	assert(isfinite(b));
	assert(roots != NULL);

	if (is_equal(a, 0)) {
		if (is_equal(b, 0)) {
			roots->n = INF_ROOTS;
			return;
		}
		roots->n = ZERO_ROOTS;
		return;
	}

	roots->n = ONE_ROOT;
	roots->x1 = -b / a;
	roots->x1 = round(roots->x1 / PRECISION) * PRECISION;

	return;
}

double calc_discrim(struct Coefficients coeffs)
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

	return fabs(x - y) <= PRECISION;
}
