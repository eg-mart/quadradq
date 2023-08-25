/** A struct representing a complex number */
struct Complex {
	/** Real part of the complex number */
	double real;
	/** Imaginary part of the complex number */
	double imag;
};

/** 
* Takes a square root of a double (may be negative) and returns a complex number
*
* @param [in] x number to take square root of (may be negative, positive or 0)
* 
* @return a complex number - square root of x
*/
struct Complex sqrt_complex(double x);

/**
* Divides a complex number by a double coefficient
*
* @param [in] a a complex number
* @param [in] b a double (dividor)
*
* @return A complex number - the result of division
*/
struct Complex divide_complex_by_const(struct Complex a, double b);

/**
* Subtracts two complex numbers
*
* @param a first complex number
* @param b second complex number
*
* @return a complex number - the result of a - b operation
*/
struct Complex subtract_complex(struct Complex a, struct Complex b);

/**
* Adds two complex numbers
*
* @param a first complex number
* @param b second complex number
*
* @return a complex number - the result of a + b operation
*/
struct Complex add_complex(struct Complex a, struct Complex b);

/**
* Multiplies a complex number by a double coefficient
*
* @param [in] a a complex number
* @param [in] b a double (coefficient)
*
* @return A complex number - the result of multiplication
*/
struct Complex multiply_complex_by_const(struct Complex a, double b);

/**
* Rounds a complex number (both real and imaginary part) to an integral value.
*
* @param a the complex number to round
*
* @return a rounded complex number
*/
struct Complex round_complex(struct Complex a);
