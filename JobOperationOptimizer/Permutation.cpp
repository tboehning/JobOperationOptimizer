#include "Permutation.h"

Permutation::Permutation(const JobList &joblist)
{
	currentIndex = 0;

	amountOperations = calculate_amount_of_operations(joblist);
	operations = new JobOperation[amountOperations];

	append_joblist(joblist);
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

void Permutation::print_permutation() const
{
	for (int i = 0; i < currentIndex; i++) {
		printf("(%d ; %d) ->  %d ; %.2f, %.2f, %.2f ;; %.2f, %.2f, %.2f\n",
			operations[i].jobNumber, operations[i].operationNumber, operations[i].toolNumber,
			operations[i].startPosition.x, operations[i].startPosition.y, operations[i].startPosition.z,
			operations[i].endPosition.x, operations[i].endPosition.y, operations[i].endPosition.z);
	}

	printf("\n");
}

int Permutation::calculate_amount_of_operations(const JobList &joblist) const
{
	int currentAmountOfOperations = 0;

	for (auto const &job : joblist.get_jobs()) {
		currentAmountOfOperations += job.get_operations().size();
	}

	return currentAmountOfOperations;
}