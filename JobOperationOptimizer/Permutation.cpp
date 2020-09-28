#include "Permutation.h"

Permutation::Permutation(const JobList &joblist)
{
	append_joblist(joblist);
}

Permutation::Permutation(const Job &job)
{
	append_job(job);
}

Permutation::Permutation()
{ }

void Permutation::append_joblist(const JobList &joblist)
{
	for (auto const &job : joblist.get_jobs()) {
		append_job(job);
	}
}

void Permutation::append_job(const Job &job)
{
	for (auto const &operation : job.get_operations()) {
		append_operation(operation);
	}
}

void Permutation::append_operation(const JobOperation &operation)
{
	operations.emplace_back(operation);
}

int Permutation::calculate_tool_changes() const
{
	unsigned int numberOfToolChanges = 0;

	for (int i = 1; i < operations.size(); i++) {
		const int INDEX_PREVIOUS_JOB = i - 1;

		const int TOOL_NUMBER_PREVIOUS_OPERATION = operations[INDEX_PREVIOUS_JOB].toolNumber;
		const int TOOL_NUMBER_CURRENT_OPERATION = operations[i].toolNumber;

		if (TOOL_NUMBER_PREVIOUS_OPERATION != TOOL_NUMBER_CURRENT_OPERATION) {
			numberOfToolChanges += 1;
		}
	}

	return numberOfToolChanges;
}

double Permutation::calculate_toolpath_from_transitions() const
{
	double lengthToolPath = 0.0;
	
	for (int i = 1; i < operations.size(); i++) {
		const int INDEX_PREVIOUS_JOB = i - 1;
	
		const Vector END_POSITION_PREVIOUS_OPERATION = operations[INDEX_PREVIOUS_JOB].endPosition;
		const Vector START_POSITION_CURRENT_OPERATION = operations[i].startPosition;
	
		lengthToolPath +=
			END_POSITION_PREVIOUS_OPERATION.calculate_distance_to_vector(START_POSITION_CURRENT_OPERATION);
	}
	
	return lengthToolPath;
}

void Permutation::print_permutation() const
{
	const int TOOL_CHANGES = calculate_tool_changes();
	const double TOOL_PATH = calculate_toolpath_from_transitions();

	printf("*** Permutation ***\n");

	for (const auto &op : operations) {
		op.print_operation();
	}

	printf("Tool Changes: %d, Toolpath length: %.2f\n", TOOL_CHANGES, TOOL_PATH);
	printf("\n");
}