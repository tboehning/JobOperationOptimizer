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

	std::vector<Job> get_jobs() const;

	void print_jobs() const;

private:
	std::vector<Job> jobs;
};

#endif