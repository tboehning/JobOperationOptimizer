#ifndef JOBDEPENDENCIES_H_
#define JOBDEPENDENCIES_H_

#include <vector>

#include "JobList.h"

class JobDependencies
{
public:
	JobDependencies();
	JobList dependencies;
};

#endif