#include "test.h"
#include <stdio.h>
#include "../equation_solver.h"

int test_quadratic(struct coefficients coeffs, struct roots rootsref);

void run_tests() {
	printf("testing...\n");
	test_quadratic({ 0, 0, 0 }, { 0, 0, INF_ROOTS });
	test_quadratic({ 1, 2, 1 }, { -1, 0, ONE_ROOT });
	test_quadratic({ 1, 0, -4 }, { -2, 2, TWO_ROOTS });
	test_quadratic({ 1, 1, 1 }, { 0, 0, ZERO_ROOTS });
}

int test_quadratic(struct coefficients coeffs, struct roots rootsref)
{
	static int test_number = 0;
	struct roots roots = { 0, 0 };
	solve_quadratic(coeffs, &roots);

	test_number++;
	if (!(is_equal(rootsref.x1, roots.x1) && is_equal(rootsref.x2, roots.x2) &&
			 is_equal(rootsref.n, roots.n))) {
		printf("test %d FAILED: x1=%lf, x2=%lf, nroots=%d,\n"
				"expected: x1=%lf, x2=%lf, nroots=%d\n", test_number, roots.x1, roots.x2,
				roots.n, rootsref.x1, rootsref.x2, rootsref.n);
		return 0;
	}

	printf("test %d OK\n", test_number);
	return 1;
}
