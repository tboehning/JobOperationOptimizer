#include "Job.h"

Job::Job(const int &number, const std::string &name) :
	number(number), name(name)
{ }

void Job::append_operation(const JobOperation &operation)
{
	operations.emplace_back(operation);
}

int Job::get_amount_of_operations() const
{
	return operations.size();
}

std::vector<JobOperation> Job::get_operations() const
{
	return operations;
}

void Job::print_job() const
{
	std::cout << "Job #" << number << " " << name << "\n";

	for (const auto &operation : operations) {
		operation.print_operation();
	}
}