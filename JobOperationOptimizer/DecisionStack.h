#ifndef DECISIONSTACK_H_
#define DECISIONSTACK_H_

#include <stack>

#include "JobList.h"

class DecisionStack
{
public:
	void append_operations_from_job(const Job &job);

	void pop_top();

	bool is_empty() const;

	JobOperation get_top() const;
	std::stack<JobOperation> get_decisions() const;
	
	void print_decisions() const;

private:
	std::stack<JobOperation> decisions;
};

#endif