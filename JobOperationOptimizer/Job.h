#ifndef JOB_H_
#define JOB_H_

#include <string>
#include <vector>
#include <algorithm>
#include <iostream>

#include "JobOperation.h"

class Job
{
public:
	std::string name;
	int number;

	Job(const int &number, const std::string &name);

	void append_operation(const JobOperation &operation);

	std::vector<JobOperation> get_operations() const;

	void print_job() const;

private:
	std::vector<JobOperation> operations;
};

#endif