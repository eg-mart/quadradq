#ifndef IO_HANDLING
#define IO_HANDLING

enum IO_error {
	NO_IO_ERR,
	FILE_ENDED,
	ERR_FILE_OPEN,
	ERR_FILE_WRITE,
	ERR_FORMAT,
	ERR_BAD_DATA,
	ERR_UNKNOWN,
	ERR_ARG_CNT,
	ERR_NO_ARGS
};

struct Flags {
	bool test_mode;
	bool use_complex;
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
void handle_arguments(int argc, char *argv[], struct Flags *flags);

#endif
