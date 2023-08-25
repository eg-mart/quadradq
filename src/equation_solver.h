#ifndef EQUATION_SOLVER
#define EQUATION_SOLVER

#include "complex.h"

/** A enum representing the number of roots in a solution */
enum Num_roots {
	/** Solution contains two complex roots */
	TWO_ROOTS_CMPLX	=	-2,
	/** There are infinite roots in a solution */
	INF_ROOTS		=	-1,
	/** No roots were found */
	ZERO_ROOTS		=	0,
	/** Solution contains one real root */
	ONE_ROOT		=	1,
	/** Solution contains two real roots */
	TWO_ROOTS		=	2
};

/** A struct containing coefficients for equation ax^2 + bx + c = 0 */
struct Coefficients {
	double a;
	double b;
	double c;
};

/** A struct containig roots and a number of them */
struct Roots_info {
	/** First root */
	struct Complex x1;
	/** Second root */
	struct Complex x2;
	/** Number of roots */
	enum Num_roots n;
};

/**
* Checks if two doubles are closer then PRECISION to each other.
* 
* @param [in] x first double value (must be finite)
* @param [in] y second double value (must be finite)
* 
* @return 1 if values are close, 0 otherwise
*/
int is_equal(double x, double y);

/**
* Solves a square equation of the form ax^2 + bx + c = 0 in complex numbers.
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
