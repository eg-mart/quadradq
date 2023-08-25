#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>

#include "colors.h"
#include "assert.h"
#include "logger.h"

struct Logger LOGGER;

void logger_ctor()
{
	LOGGER.handlers = NULL;
	LOGGER.num_handlers = 0;
}

enum Log_error add_log_handler(struct Log_handler handler)
{
	if (LOGGER.handlers == NULL) {
		LOGGER.handlers = (Log_handler*) calloc(3, sizeof(Log_handler));
		if (LOGGER.handlers == NULL) {
			return ERR_MEM;
		}
		LOGGER.capacity = 3;
	} else if (LOGGER.capacity <= LOGGER.num_handlers) {
		LOGGER.capacity += 3;
		LOGGER.handlers = (Log_handler*) realloc(LOGGER.handlers, LOGGER.capacity *
												 sizeof(Log_handler));
		if (LOGGER.handlers == NULL)
			return ERR_MEM;
	}

	LOGGER.num_handlers++;
	LOGGER.handlers[LOGGER.num_handlers - 1] = handler;

	return NO_LOG_ERR;
}

void logger_dtor()
{
	free(LOGGER.handlers);
}

enum Log_error log_message(enum Log_level level, const char *message, ...)
{
	assert(message != NULL);

	va_list args;
	va_start(args, message);

	const size_t _BUFF_SIZE = 1024;
	char buff[_BUFF_SIZE] = "";

	const char *color = NULL;
	const char *prefix = NULL;

	vsnprintf(buff, _BUFF_SIZE, message, args);

	bool error = 0;

	for (size_t i = 0; i < LOGGER.num_handlers; i++) {
		if (level < LOGGER.handlers[i].level)
			continue;

		switch (level) {
			case ERROR:
				color = RED;
				prefix = "[ERROR]";
				break;
			case WARN:
				color = YELLOW;
				prefix = "[WARNING]";
				break;
			case INFO:
				color = BLUE;
				prefix = "[INFO]";
				break;
			case DEBUG:
				color = GREEN;
				prefix = "[DEBUG]";
				break;
			default:
				color = RED;
				prefix = "[UNKNOWN]";
		}

		if (LOGGER.handlers[i].use_colors)
			fprintf(LOGGER.handlers[i].output, "%s%s %s%s",
					color, prefix, buff, RESET_COLOR);
		else
			fprintf(LOGGER.handlers[i].output, "%s %s", prefix, buff);
		error = error && ferror(LOGGER.handlers[i].output);
	}

	va_end(args);

	if (error)
		return ERR_WRITE;
	return NO_LOG_ERR;
}
