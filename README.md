# quadradq
**A minimal command line program for solving quadratic equations.**
## Key Features
* File input\output
* Solutions in complex numbers
* Robust error handling

## Usage
`quadradq [-m] [-i <path>] [-o <path>]`
* Program solves equations of the form ax^2 + bx + c = 0 with real coefficients
* The program reads 3 coefficients separated by spaces from every line, until EOF is encountered
* It outputs either roots, a string "no roots", a string "inf roots" or an error
* Use the `-m` flag to enable outputting complex solutions
* Use the `-i` and -o flags to choose input and output files respectively (*stdin* and *stdout* are used by default)

## Building
Run `make` to build the program. You'll need g++ to be installed.

Run `make testing` to build configuration with unit tests. Use the `--test` flag to run them.

Run `make html` to build html documentation with `doxygen` (you'll need to have it installed). Open `docs/html/index.html` to view the docs.

## Code Srtucture
`io_handling.h` parsing input, outputting coefficients and parsing command line arguments

`logging.h` logging messages with different importance levels to multiple files

`equation_solver.h` solving a quadratic equation of the form ax^2 + bx + c = 0 in complex numbers

`complex.h` handling complex numbers (adding, subtracting, and multiplying/dividing by a real number is supported)

`colors.h` escape codes for colors in a Linux terminal

`assert.h` a custom assert(expr) similar to one in the standard library
