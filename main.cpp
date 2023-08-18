#include <stdio.h>
#include <float.h>
#include <math.h>

enum solution_stat {
	ERR,
	NO_SOL,
	ONE_SOL,
	TWO_SOL,
	INF_SOL,
};

int isclose(double x, double y);
enum solution_stat quadsolve(double a, double b, double c, double *x1, double *x2);
enum solution_stat linsolve(double a, double b, double *x);

int main() {
	double a = 0;
	double b = 0;
	double c = 0;
	double x1 = 0;
	double x2 = 0;

	if (scanf("%lf %lf %lf", &a, &b, &c) < 3) {
		printf("Произошла ошибка ввода!");
		return -1;
	}

	enum solution_stat stat = quadsolve(a, b, c, &x1, &x2);

	switch (stat) {
		case ERR:
			printf("Произошла ошибка!");
			break;
		case NO_SOL:
			printf("Решений не найдено.");
			break;
		case ONE_SOL:
			printf("Найдено 1 решение: %.4lf", x1);
			break;
		case TWO_SOL:
			printf("Найдено 2 решения: %.4lf %.4lf", x1, x2);
			break;
		case INF_SOL:
			printf("Найдено бесконечно много решений.");
			break;
		default:
			printf("Произошла ошибка!");
	}

	return 0;
}

enum solution_stat quadsolve(double a, double b, double c, double *x1, double *x2)
{
	if (!(isfinite(a) && isfinite(b) && isfinite(c) && x1 != NULL && x2 != NULL)) {
		return ERR;
	}
	
	if (isclose(a, 0)) {
		return linsolve(b, c, x1);
	}

	double disc = b * b - 4 * a * c;

	if (disc > 0) {
		*x1 = (-b - sqrt(disc)) / (2 * a);
		*x2 = (-b + sqrt(disc)) / (2 * a);
		return TWO_SOL;
	} else if (disc < 0) {
		return NO_SOL;
	} else {
		*x1 = -b / (2 * a);
		return ONE_SOL;
	}

	return ERR;
}

enum solution_stat linsolve(double a, double b, double *x)
{
	if (!(isfinite(a) && isfinite(b) && x != NULL)) {
		return ERR;
	}

	if (isclose(a, 0)) {
		if (isclose(b, 0))
			return INF_SOL;
		else
			return NO_SOL;
	} else {
		*x = -b / a;
		return ONE_SOL;
	}

	return ERR;
}

int isclose(double x, double y)
{
	return fabs(x - y) <= DBL_EPSILON;
}
