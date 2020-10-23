#ifndef DEBUG_H_
#define DEBUG_H_

#include <string>

namespace Debug {

	#ifndef NDEBUG
		#define DEBUG_LEVEL 2	
	#endif

	void function_start(const char *functionname);
	void function_exit(const char *functionname);

	void function_log(const char *functionname, const char *message);
};

#endif