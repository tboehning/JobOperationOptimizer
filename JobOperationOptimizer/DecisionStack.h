#ifndef DECISIONSTACK_H_
#define DECISIONSTACK_H_

#include <stack>

#include "JobList.h"
#include "Job.h"
#include "JobOperation.h"

class DecisionStack
{
public:
	DecisionStack(const Job &job);

	void pop_top();

	JobOperation get_top() const;
	std::stack<JobOperation> get_decisions() const;
	
	void print_decisions() const;

private:
	std::stack<JobOperation> decisions;

	void append_operations_from_job(const Job &job);
	void append_dependencies_from_job(const Job &job);
};

#endif