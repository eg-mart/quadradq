#ifndef LOGGER_MODULE
#define LOGGER_MODULE

enum Log_level {
	DEBUG	=	0,
	INFO	=	1,
	WARN	=	2,
	ERROR	=	3
};

enum Log_error {
	NO_LOG_ERR	=	0,
	ERR_MEM		=	-1,
	ERR_WRITE	=	-2
};

struct Logger {
	unsigned int num_handlers;
	struct Log_handler *handlers;
};

struct Log_handler {
	FILE *output;
	enum Log_level level;
	bool use_colors;
};

void logger_ctor();
enum Log_error add_log_handler(struct Log_handler handler);
void logger_dtor();
enum Log_error log_message(enum Log_level level, const char *message, ...);

#endif