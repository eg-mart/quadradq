#include <stdio.h>
#include <float.h>
#include <math.h>

int isclose(double x, double y);
int quadsolve(double a, double b, double c, double *x1, double *x2);

int main() {
	double a, b, c, x1, x2;

	if (scanf("%lf %lf %lf", &a, &b, &c) < 3) {
		printf("Произошла ошибка ввода!");
		return -1;
	}

	int stat = quadsolve(a, b, c, &x1, &x2);

	if (stat < 0)
		printf("Решений не найдено.");
	else if (stat == 0)
		printf("Найдено 1 решение: %.4lf", x1);
	else
		printf("Найдено 2 решения: %.4lf %.4lf", x1, x2);

	return 0;
}

int quadsolve(double a, double b, double c, double *x1, double *x2)
{
	if (!(isfinite(a) && isfinite(b) && isfinite(c))) {
		return -1;
	}
	
	if (isclose(a, 0)) {
		if (isclose(b, 0)) {
			return -1;
		} else {
			*x1 = -c / b;
			return 0;
		}
	}

	double disc = b * b - 4 * a * c;

	if (disc > 0) {
		*x1 = (-b - sqrt(disc)) / (2 * a);
		*x2 = (-b + sqrt(disc)) / (2 * a);
		return 1;
	} else if (disc < 0) {
		return -1;
	} else {
		*x1 = -b / (2 * a);
		return 0;
	}

	return -1;
}

int isclose(double x, double y)
{
	return fabs(x - y) <= DBL_EPSILON;
}
