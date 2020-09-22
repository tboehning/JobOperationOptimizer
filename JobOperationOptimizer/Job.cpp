#include "Job.h"

Job::Job()
{ }

void Job::append_operation(const JobOperation &operation)
{
	operations.push_back(operation);
}

std::vector<JobOperation> Job::get_operations() const
{
	return operations;
}

void Job::print_job() const
{
	for (const auto &operation : operations) {
		printf("   (%d ; %d) ->  %d ; %.2f, %.2f, %.2f ;; %.2f, %.2f, %.2f\n",
			operation.jobNumber, operation.operationNumber, operation.toolNumber,
			operation.startPosition.x, operation.startPosition.y, operation.startPosition.z,
			operation.endPosition.x, operation.endPosition.y, operation.endPosition.z);
	}
}