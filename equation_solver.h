const int INF_ROOTS = -1;

struct coefficients {
	double a;
	double b;
	double c;
};

struct roots {
	double x1;
	double x2;
	int n;
};

int is_equal(double x, double y);
void solve_quadratic(struct coefficients coeffs, struct roots *roots);
void solve_linear(double a, double b, struct roots *roots);
double calc_discrim(struct coefficients coeffs);

