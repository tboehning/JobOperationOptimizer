#include "DecisionVector.h"

void DecisionVector::append_operations_from_job(const Job &job)
{
	for (const auto &operation : job.get_operations()) {
		decisions.push_back(operation);
	}
}

JobOperation DecisionVector::get_operation_at_position(const int &position) const
{
	return decisions[position];
}

int DecisionVector::get_size() const
{
	return decisions.size();
}

void DecisionVector::print_decisions() const
{
	std::cout << "*** DecisionVector ***" << "\n";

	for (const auto &operation : decisions) {
		operation.print_operation();
	}
}
