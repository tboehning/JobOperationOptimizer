#include "Job.h"

Job::Job(const int &number, const std::string &name) :
	number(number), name(name)
{ }

void Job::append_operation(const JobOperation &operation)
{
	operations.push_back(operation);
}

void Job::append_dependency(const Job &dependency)
{
	dependencies.push_back(dependency);
}

int Job::get_amount_of_operations() const
{
	return operations.size();
}

std::vector<JobOperation> Job::get_operations() const
{
	return operations;
}

std::vector<Job> Job::get_dependencies() const
{
	return dependencies;
}

void Job::print_job() const
{
	std::cout << "Job #" << number << " " << name << "\n";

	for (const auto &operation : operations) {
		operation.print_operation();
	}

	for (const auto &dependency : dependencies) {
		std::cout << "   +++ Dependency: #" << dependency.number << " " << dependency.name << "\n";
	}
}