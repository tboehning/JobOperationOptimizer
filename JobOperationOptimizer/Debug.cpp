#include "Debug.h"

void Debug::function_start(const char *functionname)
{ 
	#ifndef NDEBUG
		printf("%s > Start \n", functionname);
	#endif
}

void Debug::function_exit(const char *functionname)
{
	#ifndef NDEBUG
		printf("%s > Exit \n\n", functionname);
	#endif
}

void Debug::function_log(const char *functionname, const char *message)
{
	#ifndef NDEBUG
		if (DEBUG_LEVEL > 1) {
			printf("%s > Log (Level %i) : %s\n", functionname, DEBUG_LEVEL, message);
		}
	#endif
}
