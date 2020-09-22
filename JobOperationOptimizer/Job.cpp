#include "Job.h"
#include "JobDependencies.h"

Job::Job(const int &number, const std::string &name) :
	number(number), name(name)
{ 
	dependencies = new JobDependencies;
}

void Job::append_operation(const JobOperation &operation)
{
	operations.push_back(operation);
}

void Job::append_job_dependency(const Job &dependency)
{
	dependencies->dependencies.append_job(dependency);
}

std::vector<JobOperation> Job::get_operations() const
{
	return operations;
}

JobDependencies* Job::get_dependencies() const
{
	return dependencies;
}

void Job::print_job() const
{
	std::cout << "Job #" << number << " " << name << "\n";

	for (const auto &operation : operations) {
		operation.print_operation();
	}

	for (const auto &dependency : dependencies->dependencies.get_jobs()) {
		std::cout << "   +++ Dependency: #" << dependency.number << " " << dependency.name << "\n";
	}
}