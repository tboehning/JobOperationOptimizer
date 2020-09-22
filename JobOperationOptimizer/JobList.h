#ifndef JOBLIST_H_
#define JOBLIST_H_

#include <vector>
#include <string>

#include "Job.h"

class JobList
{
public:
	JobList();

	void append_job(const Job &job);

	int calculate_tool_changes() const;
	double calculate_toolpath_from_transitions() const;

	std::vector<Job> get_jobs() const;

	void print_information() const;

private:
	std::vector<Job> jobs;

	int calculate_tool_changes_between_jobs() const;
	double calculate_toolpath_from_transitions_between_jobs() const;
};

#endif