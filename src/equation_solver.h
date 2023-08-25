#ifndef EQUATION_SOLVER
#define EQUATION_SOLVER

enum Num_roots {
	INF_ROOTS	=	-1,
	ZERO_ROOTS	=	0,
	ONE_ROOT	=	1,
	TWO_ROOTS	=	2
};

struct Coefficients {
	double a;
	double b;
	double c;
};

struct Roots_info {
	double x1;
	double x2;
	enum Num_roots n;
};

/**
* Checks if two doubles are closer then DBL_EPSILON to each other.
* 
* @param [in] x first double value (must be finite)
* @param [in] y second double value (must be finite)
* 
* @return 1 if values are close, 0 otherwise
*/
int is_equal(double x, double y);

/**
* Solves a square equation of the form ax^2 + bx + c = 0.
*
* @param [in]  coeffs a sctruct containing a, b and c coefficients
* @param [out] roots  a pointer to a struct containing roots x1, x2 and a number of roots
*/
void solve_quadratic(struct Coefficients coeffs, struct Roots_info *roots);

/**
* Solves a linear equation of the form ax + b = 0.
* 
* @param [in]  a     a-coefficient (must be finite)
* @param [in]  b     b-coefficient (must be finite)
* @param [out] roots a pointer to a struct containing roots x1, x2 and a number of roots
*/
void solve_linear(double a, double b, struct Roots_info *roots);

#endif
