#include "JobList.h"

JobList::JobList()
{ }

void JobList::append_job(const Job &job)
{
	jobs.emplace_back(job);
}

std::vector<Job> JobList::get_jobs() const
{
	return jobs;
}

int JobList::get_amount_of_jobs() const
{
	return jobs.size();
}

int JobList::get_amount_of_operations() const
{
	int amountOfOperations = 0;

	for (const auto &job : jobs) {
		amountOfOperations += job.get_amount_of_operations();
	}

	return amountOfOperations;
}

void JobList::print_jobs() const
{
	printf("*** JobList ***\n");

	for (auto const &job : jobs) {
		job.print_job();
	}
	printf("\n");
}