#ifndef PERMUTATIONPOINTER_H_
#define PERMUTATIONPOINTER_H_

#include "JobList.h"

class PermutationPointer
{
public:
	PermutationPointer(const JobList &joblist);
	PermutationPointer(const Job &job);
	PermutationPointer(const int &size);
	PermutationPointer();

	void append_joblist(const JobList &joblist);
	void append_job(const Job &job);
	void append_operation(const JobOperation &operation);

	int calculate_tool_changes() const;
	double calculate_toolpath_from_transitions() const;

	std::vector<const JobOperation*> get_operations() const;

	int get_amount_of_operations() const;

	void print_permutation() const;

private:
	std::vector<const JobOperation*> operations;
};

#endif