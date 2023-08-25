#include <math.h>
#include <float.h>

#include "assert.h"
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

	double discmnt = coeffs.b * coeffs.b - 4 * coeffs.a * coeffs.c;

	struct Complex sqrt_discmnt = sqrt_complex(discmnt);
	struct Complex neg_b = { -coeffs.b, 0 };
	roots->x1 = divide_complex_by_const(subtract_complex(neg_b, sqrt_discmnt),
										2 * coeffs.a);
	roots->x2 = divide_complex_by_const(add_complex(neg_b, sqrt_discmnt),
										2 * coeffs.a);

	struct Complex tmp = { NAN, NAN };

	tmp = round_complex(multiply_complex_by_const(roots->x1, 1 / PRECISION));
	roots-> x1 = multiply_complex_by_const(tmp, PRECISION);

	tmp = round_complex(multiply_complex_by_const(roots->x2, 1 / PRECISION));
	roots-> x2 = multiply_complex_by_const(tmp, PRECISION);

	if (discmnt < 0) {
		roots->n = TWO_ROOTS_CMPLX;
		return;
	}

	if (discmnt > 0) {
		roots->n = TWO_ROOTS;
		return;
	}

	roots->n = ONE_ROOT;
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
	roots->x1 = { -b / a, 0 };
}

int is_equal(double x, double y)
{
	assert(isfinite(x));
	assert(isfinite(y));

	return fabs(x - y) <= PRECISION;
}
