#include "Job.h"

Job::Job()
{ }

void Job::append_operation(const JobOperation &operation)
{
	operations.push_back(operation);
}

int Job::calculate_tool_changes() const
{
	unsigned int numberOfToolChanges = 0;

	for (int i = 1; i < operations.size(); i++) {
		int previousTool = i - 1;
		numberOfToolChanges += calculate_tool_change(operations[previousTool], operations[i]);
	}

	return numberOfToolChanges;
}

double Job::calculate_toolpath_from_transitions() const
{
	double lengthToolpath = 0.0;

	for (int i = 1; i < operations.size(); i++) {
		const int POSITION_PREVIOUS_OPERATION = i - 1;
		Vector endPositionPreviousOperation = operations[POSITION_PREVIOUS_OPERATION].endPosition;

		lengthToolpath += endPositionPreviousOperation.calculate_distance_to_vector(operations[i].startPosition);
	}

	return lengthToolpath;
}

std::vector<JobOperation> Job::get_operations() const
{
	return operations;
}

int Job::calculate_tool_change(const JobOperation &task1, const JobOperation &task2) const
{
	int toolChanges = (task1.toolNumber == task2.toolNumber) ? 0 : 1;

	return toolChanges;
}

void Job::print_job() const
{
	for (const auto &operation : operations) {
		printf("(%d ; %d) ->  %d ; %.2f, %.2f, %.2f ;; %.2f, %.2f, %.2f\n",
			operation.jobNumber, operation.operationNumber, operation.toolNumber,
			operation.startPosition.x, operation.startPosition.y, operation.startPosition.z,
			operation.endPosition.x, operation.endPosition.y, operation.endPosition.z);
	}
	printf("\n");
}

void Job::print_job_information() const
{
	const int SIZE_JOB = operations.size();
	const int NUMBER_OF_TOOLCHANGES = calculate_tool_changes();
	const double LENGTH_TOOLPATH = calculate_toolpath_from_transitions();

	printf("*** Job Information (sorted, unoptimized) ***\n");
	printf("Number of Operations: %d\n", SIZE_JOB);
	printf("Number of Toolchanges: %d\n", NUMBER_OF_TOOLCHANGES);
	printf("Length transition tool paths: %f\n\n", LENGTH_TOOLPATH);
}