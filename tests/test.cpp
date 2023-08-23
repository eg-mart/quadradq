#include "test.h"

const int NUM_TESTS = 4;

struct Test_case {
	Coefficients coeffs;
	Roots_info roots;
};

struct Test_case tests[] = {
	{ { 1, 2,  1 }, { -1, 0, ONE_ROOT } },
	{ { 0, 0,  0 }, {  0, 0, INF_ROOTS } },
	{ { 1, 0, -4 }, { -2, 2, TWO_ROOTS } },
	{ { 1, 1,  1 }, {  0, 0, ZERO_ROOTS } },
};

void test_quadratic(int test_num, struct Test_case test);

void run_tests() {
	printf("testing...\n");

	for (int i = 0; i < NUM_TESTS; i++)
		test_quadratic(i + 1, tests[i]);
}

void test_quadratic(int test_num, struct Test_case test)
{
	struct Roots_info roots = { 0, 0 };
	solve_quadratic(test.coeffs, &roots);

	if (!(is_equal(test.roots.x1, roots.x1) && is_equal(test.roots.x2, roots.x2) &&
			 is_equal(test.roots.n, roots.n))) {
		printf("test %d FAILED: x1=%lf, x2=%lf, nroots=%d,\n"
				"expected: x1=%lf, x2=%lf, nroots=%d\n", test_num, roots.x1, roots.x2,
				roots.n, test.roots.x1, test.roots.x2, test.roots.n);
		return;
	}

	printf("test %d OK\n", test_num);
}
