#ifndef DECISIONVECTOR_H_
#define DECISIONVECTOR_H_

#include "JobList.h"

class DecisionVector
{
public:
	void append_operations_from_job(const Job &job);

	const JobOperation* get_operation_at_position(const int &position) const;

	int get_size() const;

	void print_decisions() const;

private:
	std::vector<JobOperation> decisions;
};

#endif