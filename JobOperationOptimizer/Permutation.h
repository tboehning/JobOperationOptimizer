#ifndef PERMUTATION_H_
#define PERMUTATION_H_

#include "JobList.h"

class Permutation
{
public:
	Permutation(const JobList &joblist);
	Permutation(const Job &job);
	Permutation(const int &sizearray);
	~Permutation();

	void append_joblist(const JobList &joblist);
	void append_job(const Job &job);
	void append_operation(const JobOperation &operation);

	int calculate_tool_changes() const;
	double calculate_toolpath_from_transitions() const;

	void print_permutation() const;

private:
	JobOperation *operations;

	int amountOperations;
	int currentIndex;
	int calculate_amount_of_operations(const JobList &joblist) const;
	int calculate_amount_of_operations(const Job &job) const;
};

#endif