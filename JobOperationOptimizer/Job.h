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
	void append_dependency(const Job &dependency);

	int get_size_operations() const;
	std::vector<JobOperation> get_operations() const;
	std::vector<Job> get_dependencies() const;

	void print_job() const;

private:
	std::vector<JobOperation> operations;
	std::vector<Job> dependencies;
};

#endif