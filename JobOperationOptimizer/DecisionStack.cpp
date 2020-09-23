#include "DecisionStack.h"

DecisionStack::DecisionStack(const Job &job)
{
	append_operations_from_job(job);
	append_dependencies_from_job(job);
}

std::stack<JobOperation> DecisionStack::get_decisions() const
{
	return decisions;
}

void DecisionStack::append_operations_from_job(const Job &job)
{
	for (int i = job.get_size() - 1; i >= 0; i--) {
		decisions.push(job.get_operations()[i]);
	}
}

void DecisionStack::append_dependencies_from_job(const Job &job)
{
	std::vector<Job> dependencies = job.get_dependencies();

	for (int i = dependencies.size() - 1; i >= 0; i--) {
		append_operations_from_job(dependencies[i]);
	}
}

void DecisionStack::print_decisions() const
{
	std::stack<JobOperation> tempStack = decisions;

	while (!tempStack.empty()) {
		printf("HERE");
		tempStack.top().print_operation();
		tempStack.pop();
	}
}
