struct Complex {
	double real;
	double imag;
};

struct Complex sqrt_complex(double x);
struct Complex divide_complex_by_const(struct Complex a, double b);
struct Complex subtract_complex(struct Complex a, struct Complex b);
struct Complex add_complex(struct Complex a, struct Complex b);
struct Complex multiply_complex_by_const(struct Complex a, double b);
struct Complex round_complex(struct Complex a);
