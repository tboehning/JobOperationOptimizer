#ifndef JOB_H_
#define JOB_H_

#include <string>
#include <vector>
#include <algorithm>
#include <iostream>

#include "JobOperation.h"

class JobDependencies;

class Job
{
public:
	std::string name;
	int number;

	Job(const int &number, const std::string &name);

	void append_operation(const JobOperation &operation);
	void append_job_dependency(const Job &dependency);

	std::vector<JobOperation> get_operations() const;
	JobDependencies* get_dependencies() const;

	void print_job() const;

private:
	std::vector<JobOperation> operations;

	JobDependencies *dependencies;
};

#endif