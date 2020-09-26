#include "JobList.h"

JobList::JobList()
{ }

void JobList::append_job(const Job &job)
{
	jobs.push_back(job);
}

std::vector<Job> JobList::get_jobs() const
{
	return jobs;
}

int JobList::get_amount_of_operations() const
{
	return jobs.size();
}

void JobList::print_jobs() const
{
	printf("*** JobList ***\n");

	for (auto const &job : jobs) {
		job.print_job();
	}
	printf("\n");
}