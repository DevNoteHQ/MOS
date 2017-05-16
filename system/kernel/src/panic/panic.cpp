#include <stdnoreturn.h>
#include <stdarg.h>
#include <panic/panic.hpp>

void panic(const char *message, ...)
{
	/*
	va_list args;
	va_start(args, message);
	vspanic(message, 0, args);
	va_end(args);
	*/
}