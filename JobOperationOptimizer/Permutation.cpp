#include "Permutation.h"

Permutation::Permutation(const JobList &joblist)
{
	currentIndex = 0;

	amountOperations = calculate_amount_of_operations(joblist);
	operations = new JobOperation[amountOperations];

	append_joblist(joblist);
}

Permutation::Permutation(const Job &job)
{
	currentIndex = 0;

	amountOperations = calculate_amount_of_operations(job);
	operations = new JobOperation[amountOperations];

	append_job(job);
}

Permutation::Permutation(const int &sizearray)
{
	currentIndex = 0;

	amountOperations = sizearray;

	operations = new JobOperation[amountOperations];
}

Permutation::~Permutation()
{
	delete[] operations;
}

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
	operations[currentIndex] = operation;

	currentIndex += 1;
}

int Permutation::calculate_tool_changes() const
{
	unsigned int numberOfToolChanges = 0;

	for (int i = 1; i < currentIndex; i++) {
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
	int lengthToolPath = 0.0;
	
	for (int i = 1; i < currentIndex; i++) {
		const int INDEX_PREVIOUS_JOB = i - 1;
	
		const Vector END_POSITION_PREVIOUS_OPERATION = operations[INDEX_PREVIOUS_JOB].endPosition;
		const Vector START_POSITION_CURRENT_OPERATION = operations[i].startPosition;
	
		lengthToolPath +=
			END_POSITION_PREVIOUS_OPERATION.calculate_distance_to_vector(START_POSITION_CURRENT_OPERATION);
	}
	
	return lengthToolPath;
}

int Permutation::calculate_amount_of_operations(const JobList &joblist) const
{
	int currentAmountOfOperations = 0;

	for (auto const &job : joblist.get_jobs()) {
		currentAmountOfOperations += job.get_operations().size();
	}

	return currentAmountOfOperations;
}

int Permutation::calculate_amount_of_operations(const Job &job) const
{
	int currentAmountOfOperations = 0;

	for (auto const &operation : job.get_operations()) {
		currentAmountOfOperations += 1;
	}

	return currentAmountOfOperations;
}

void Permutation::print_permutation() const
{
	const int TOOL_CHANGES = calculate_tool_changes();
	const double TOOL_PATH = calculate_toolpath_from_transitions();

	printf("*** Permutation ***\n");

	for (int i = 0; i < currentIndex; i++) {
		operations[i].print_operation();
	}

	printf("Tool Changes: %d, Toolpath length: %.2f\n", TOOL_CHANGES, TOOL_PATH);
	printf("\n");
}