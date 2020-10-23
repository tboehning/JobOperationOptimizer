#ifndef PERMUTATION_H_
#define PERMUTATION_H_

#include "JobList.h"

class Permutation
{
public:
	Permutation(const JobList &joblist);
	Permutation(const Job &job);
	Permutation(const int &size);
	Permutation();

	void append_joblist(const JobList &joblist);
	void append_job(const Job &job);
	void append_operation(const JobOperation &operation);

	int calculate_tool_changes() const;
	double calculate_toolpath_from_transitions() const;

	std::vector<JobOperation> get_operations() const;

	int get_amount_of_operations() const;

	void print_permutation() const;

private:
	std::vector<JobOperation> operations;
};

#endif