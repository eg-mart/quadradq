enum nroots {
	ZERO_ROOTS,
	ONE_ROOT,
	TWO_ROOTS,
	INF_ROOTS
};

struct coefficients {
	double a;
	double b;
	double c;
};

struct roots {
	double x1;
	double x2;
	enum nroots n;
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
void solve_quadratic(struct coefficients coeffs, struct roots *roots);

/**
* Solves a linear equation of the form ax + b = 0.
* 
* @param [in]  a     a-coefficient (must be finite)
* @param [in]  b     b-coefficient (must be finite)
* @param [out] roots a pointer to a struct containing roots x1, x2 and a number of roots
*/
void solve_linear(double a, double b, struct roots *roots);

/**
* Calculates a discriminant for a given equation ax^2 + bx + c = 0.
*
* @param [in] coeffs a struct containing a, b and c coefficients
*
* @return a discriminant value
*/
double calc_discrim(struct coefficients coeffs);
