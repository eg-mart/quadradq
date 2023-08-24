#ifndef MY_ASSERT
#define MY_ASSERT

#include <stdio.h>

#ifdef NDEBUG
#	define assert(condition) ((void)0)
#else
#	define assert(condition) if (!(condition)) {\
								fprintf(stderr, "\033[0m\033[31m[Assert failed] %s:%d "\
										"in function %s: %s is FALSE\033[0m\n",\
										__FILE__, __LINE__, __func__, #condition);\
								abort();\
							}
#endif

#endif

