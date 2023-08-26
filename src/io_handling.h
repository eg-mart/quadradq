#ifndef IO_HANDLING
#define IO_HANDLING

/** An enum of possible IO errors (including command line arguments parsing) */
enum IO_error {
	/** No arguments were found. Is not an error */
	NO_ARGS			=	2,
	/** Input file ended. Is not an error */
	FILE_ENDED		=	1,
	/** No IO errors happened */
	NO_IO_ERR		=	0,
	/** Error happened while trying to open a file */
	ERR_FILE_OPEN	=	-1,
	/** Error happened while writing to a file */
	ERR_FILE_WRITE	=	-2,
	/** Data has a wrong format and could not be parsed */
	ERR_FORMAT		=	-3,
	/** Data is bad (contains values like NAN or INF) */
	ERR_BAD_DATA	=	-4,
	/** An unknown error occured */
	ERR_UNKNOWN		=	-5,
	/** A wrong argument (or flag) was encountered */
	ERR_WRONG_ARG	=	-6,
	/** No filename was found where it should have been in command arguments */
	ERR_NO_FILENAME	=	-7
};

/** A struct containing flags and input/output filenames from the command line. */
struct Args {
	/** A flag that controls whether unit testing will run instead of the program */
	bool test_mode;
	/** A flag that determines whether program will output complex numbers */
	bool use_complex;
	/** Input filename */
	const char *input_filename;
	/** Output filename */
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
* @param [out] output      pointer to the output file
* @param [in]  roots       a struct containing x1, x2 roots
* @param [in]  use_complex whether to output complex numbers or "no roots"
*
* @return NO_IO_ERR if no errors were encountered, error code otherwise
*/
enum IO_error output_roots(FILE *output, struct Roots_info roots, bool use_complex);

/**
* Logs a message corresponding to the error code using the logger module.
*
* @param [in]  err_code an error code from the IO_error enum
*/
void log_error(enum IO_error err_code);

/**
* Parses command line arguments for flags and filenames.
*
* @param [in]  argc the number of arguments
* @param [in]  argv array of pointers to arguments
* @param [out] args pointer to a struct containing flags and input/output filenames
*/
enum IO_error handle_arguments(int argc, char *argv[], struct Args *args);

#endif
