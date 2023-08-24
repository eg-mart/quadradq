#include "test.h"
#include "../colors.h"

struct Test_case {
	Coefficients coeffs;
	Roots_info roots;
};

struct Test_case tests[] = {
	{ { 1, 2,  1 }, { -1, 0, ONE_ROOT   } },
	{ { 0, 0,  0 }, {  0, 0, INF_ROOTS  } },
	{ { 1, 0, -4 }, { -2, 2, TWO_ROOTS  } },
	{ { 1, 1,  1 }, {  0, 0, ZERO_ROOTS } },
	{ { 1, 1,  1 }, {  0, 0, ONE_ROOT   } },
};

void test_quadratic(int test_num, const struct Test_case *test);

void run_tests() {
	printf("testing...\n");

	int num_tests = sizeof(tests) / sizeof(Test_case);
	for (int i = 0; i < num_tests; i++)
		test_quadratic(i + 1, &tests[i]);
}

void test_quadratic(int test_num, const struct Test_case *test)
{
	struct Roots_info roots = { 0, 0 };
	solve_quadratic(test->coeffs, &roots);

	if (!(is_equal(test->roots.x1, roots.x1) && is_equal(test->roots.x2, roots.x2) &&
			 is_equal(test->roots.n, roots.n))) {
		printf("%stest %d FAILED:%s x1=%lf, x2=%lf, nroots=%d,\n"
				"expected: x1=%lf, x2=%lf, nroots=%d\n", RED, test_num, RESET_COLOR,
				roots.x1, roots.x2, roots.n, test->roots.x1, 
				test->roots.x2, test->roots.n);
		return;
	}

	printf("%stest %d OK%s\n", GREEN, test_num, RESET_COLOR);
}
