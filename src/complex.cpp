#include <math.h>

#include "complex.h"

struct Complex sqrt_complex(double x)
{
	if (x < 0) 
		return { 0, sqrt(fabs(x)) };
	else
		return { sqrt(x), 0 };
}

struct Complex add_complex(struct Complex a, struct Complex b)
{
	return { a.real + b.real, a.imag + b.imag };
}

struct Complex subtract_complex(struct Complex a, struct Complex b)
{
	return { a.real - b.real, a.imag - b.imag };
}

struct Complex divide_complex_by_const(struct Complex a, double b)
{
	return { a.real / b, a.imag / b };
}

struct Complex multiply_complex_by_const(struct Complex a, double b)
{
	return { a.real * b, a.imag * b };
}

struct Complex round_complex(struct Complex a)
{
	return { round(a.real), round(a.imag) };
}
