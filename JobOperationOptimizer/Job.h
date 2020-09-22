#ifndef JOB_H_
#define JOB_H_

#include <vector>
#include <algorithm>

#include "JobOperation.h"

class Job
{
public:
	std::vector<JobOperation> operations;

	Job();

	void append_operation(const JobOperation &operation);

	int calculate_tool_changes() const;
	double calculate_toolpath_from_transitions() const;

	std::vector<JobOperation> get_operations();

	void print_job() const;
	void print_job_information() const;

private:
	int calculate_tool_change(const JobOperation &task1, const JobOperation &task2) const;
};

#endif