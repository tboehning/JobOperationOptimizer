#include "Debug.h"

void Debug::function_start(const char *functionname)
{ 
	if (DEBUG_LEVEL > 0) {
		std::cout << functionname << " > Start\n";
	}
}

void Debug::function_exit(const char *functionname)
{
	if (DEBUG_LEVEL > 0) {
		std::cout << functionname << " > Exit\n";
	}
}

void Debug::function_log(const char *functionname, ...)
{
	va_list arguments;
	va_start(arguments, functionname);

	if (DEBUG_LEVEL > 1) {
		std::cout << functionname << " > Log > " << va_arg(arguments, const char*) << "\n";
	}

}
