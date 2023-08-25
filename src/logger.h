#ifndef LOGGER_MODULE
#define LOGGER_MODULE

enum Log_level {
	DEBUG,
	INFO,
	WARN,
	ERROR
};

enum Log_error {
	NO_LOG_ERR,
	ERR_MEM,
	ERR_WRITE
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

void init_logger();
enum Log_error add_log_handler(struct Log_handler handler);
void close_logger();
enum Log_error log_message(enum Log_level level, const char *message, ...);

#endif