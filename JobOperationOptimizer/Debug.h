#ifndef DEBUG_H_
#define DEBUG_H_

#include <iostream>
#include <cstdarg>

namespace Debug {
	#define DEBUG_LEVEL 2

	void function_start(const char *functionname);
	void function_exit(const char *functionname);

	void function_log(const char *functionname, ...);
};

#endif