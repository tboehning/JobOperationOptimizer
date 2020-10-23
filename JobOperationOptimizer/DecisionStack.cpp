#include "DecisionStack.h"

void DecisionStack::pop_top()
{
	decisions.pop();
}

bool DecisionStack::is_empty() const
{
	return decisions.empty();
}

std::stack<JobOperation> DecisionStack::get_decisions() const
{
	return decisions;
}

JobOperation DecisionStack::get_top() const
{
	return decisions.top();
}

void DecisionStack::append_operations_from_job(const Job &job)
{
	for (int i = job.get_amount_of_operations() - 1; i >= 0; i--) {
		decisions.push(job.get_operations()[i]);
	}
}

void DecisionStack::print_decisions() const
{
	printf("*** DecisionStack ***\n");

	std::stack<JobOperation> tempStack = decisions;

	while (!tempStack.empty()) {
		tempStack.top().print_operation();
		tempStack.pop();
	}
}