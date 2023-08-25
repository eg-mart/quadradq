#include "test.h"
#include "logger.h"
#include "equation_solver.h"

struct Test_case {
	Coefficients coeffs;
	Roots_info roots;
};

struct Test_case tests[] = {
	{ { 0, 0,  0 }, { {  0,  0 }, {    0, 0 }, INF_ROOTS       } },
	{ { 1, 4,  5 }, { { -2, -1 }, {   -2, 1 }, TWO_ROOTS_CMPLX } },
	{ { 1, 2,  1 }, { { -1,  0 }, {   -1, 0 }, ONE_ROOT        } },
	{ { 1, 0, -4 }, { { -2,  0 }, {    2, 0 }, TWO_ROOTS       } },
	{ { 0, 2,  4 }, { { -2,  0 }, {    0, 0 }, ONE_ROOT        } },
	{ { 0, 0,  1 }, { {  0,  0 }, {    0, 0 }, ZERO_ROOTS      } },
	{ { 2, 5,  2 }, { { -2,  0 }, { -0.5, 0 }, TWO_ROOTS       } },
};

void test_quadratic(int num_test, const struct Test_case *test);

void run_tests() {
	int num_tests = sizeof(tests) / sizeof(Test_case);
	for (int i = 0; i < num_tests; i++)
		test_quadratic(i + 1, &tests[i]);
}

void test_quadratic(int num_test, const struct Test_case *test)
{
	struct Roots_info roots = { { 0, 0 }, { 0, 0 } };
	solve_quadratic(test->coeffs, &roots);

	if (!(is_equal(test->roots.x1.real, roots.x1.real) &&
		  is_equal(test->roots.x2.real, roots.x2.real) &&
		  is_equal(test->roots.x1.imag, roots.x1.imag) &&
		  is_equal(test->roots.x2.imag, roots.x2.imag) &&
		  is_equal(test->roots.n, roots.n))) {
		log_test(false, num_test, "x1=%lf, x2=%lf, nroots=%d,\n"
				 "expected: x1=%lf, x2=%lf, nroots=%d\n",
				 roots.x1.real, roots.x2.real, roots.n, test->roots.x1.real,
				 test->roots.x2.real, test->roots.n);
		return;
	}

	log_test(true, num_test, "\n");
}
