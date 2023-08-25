#ifndef IO_HANDLING
#define IO_HANDLING

enum IO_error {
	NO_ARGS			=	2,
	FILE_ENDED		=	1,
	NO_IO_ERR		=	0,
	ERR_FILE_OPEN	=	-1,
	ERR_FILE_WRITE	=	-2,
	ERR_FORMAT		=	-3,
	ERR_BAD_DATA	=	-4,
	ERR_UNKNOWN		=	-5,
	ERR_WRONG_ARG	=	-6,
	ERR_NO_FILENAME	=	-7
};

struct Args {
	bool test_mode;
	bool use_complex;
	const char *input_filename;
	const char *output_filename;
};

/**
* Reads coefficients from a file. Returns error in case of a wrong data format,
* returns FILE_ENDED when EOF is encountered
*
* @param [in]  input  pointer to the input file (can't be NULL)
* @param [out] coeffs pointer to a struct with a, b, c coefficients (can't be NULL)
*
* @return NO_IO_ERR if no errors were encountered, error code otherwise
*/
enum IO_error input_coefficients(FILE *input, struct Coefficients *coeffs);

/**
* Writes roots to a file. Returns error in case writing failed.
*
* @param [out] output pointer to the output file
* @param [in]  roots  a struct containing x1, x2 roots
*
* @return NO_IO_ERR if no errors were encountered, error code otherwise
*/
enum IO_error output_roots(FILE *output, struct Roots_info roots);

/**
* Writes a message corresponding to the error code to the error file.
*
* @param [out] error    the output file
* @param [in]  err_code an error code from the error enum
*/
void log_error(enum IO_error err_code);

/**
* Parses command line arguments for the testing mode flag
*
* @param [in]  argc      the number of arguments
* @param [in]  argv      array of pointers to arguments
* @param [out] test_mode pointer to a testing mode flag
*/
enum IO_error handle_arguments(int argc, char *argv[], struct Args *args);

#endif
