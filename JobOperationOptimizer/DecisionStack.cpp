#include "DecisionStack.h"

void DecisionStack::pop_top()
{
	decisions.pop();
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

void DecisionStack::append_dependencies_recursively_from_job(const Job &job)
{
	std::vector<Job> dependencies = job.get_dependencies();

	for (int i = dependencies.size() - 1; i >= 0; i--) {
		append_operations_from_job(dependencies[i]);
		append_dependencies_recursively_from_job(dependencies[i]);
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