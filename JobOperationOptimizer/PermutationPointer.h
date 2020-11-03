#ifndef PERMUTATIONPOINTER_H_
#define PERMUTATIONPOINTER_H_

#include <vector>

#include "JobOperation.h"


class PermutationPointer
{
public:
	PermutationPointer(const int &size);

	void append_operation(const JobOperation &operation);

	int calculate_tool_changes() const;
	double calculate_toolpath_from_transitions() const;

	void print_permutation() const;

private:
	std::vector<JobOperation*> operations;

	int index;
};

#endif