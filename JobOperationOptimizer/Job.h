#ifndef JOB_H_
#define JOB_H_

#include <vector>
#include <algorithm>

#include "JobOperation.h"

class Job
{
public:
	Job();

	void append_operation(const JobOperation &operation);

	std::vector<JobOperation> get_operations() const;

	void print_job() const;

private:
	std::vector<JobOperation> operations;
};

#endif