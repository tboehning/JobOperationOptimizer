#include "PermutationBoundaries.h"

PermutationBoundaries::PermutationBoundaries()
{
}

PermutationBoundaries::PermutationBoundaries(const int &amountofoperations)
{
	init_minimal_amount_vector(amountofoperations);
}

void PermutationBoundaries::check_and_update_minimal_amount_vector(const Permutation &bestpermutationnode)
{
	const long long AMOUNT_OF_OPERATIONS_PERMUTATION = bestpermutationnode.get_amount_of_operations();

	if (AMOUNT_OF_OPERATIONS_PERMUTATION >= 2) {
		const int AMOUNT_TOOLCHANGES_PERMUTATION = bestpermutationnode.calculate_tool_changes();

		{
			std::lock_guard<std::mutex> lockGuard(vectorMutex);

			if (AMOUNT_TOOLCHANGES_PERMUTATION < currentMinimalAmountToolChangesForCertainPermutationLength[AMOUNT_OF_OPERATIONS_PERMUTATION - 1]) {
				currentMinimalAmountToolChangesForCertainPermutationLength[AMOUNT_OF_OPERATIONS_PERMUTATION - 1] = AMOUNT_TOOLCHANGES_PERMUTATION;
			}
		}
	}
}

void PermutationBoundaries::print_vector() const
{
	for (int i = 0; i < currentMinimalAmountToolChangesForCertainPermutationLength.size(); i++) {
		printf("%d: %d\n", i, currentMinimalAmountToolChangesForCertainPermutationLength[i]);
	}
}

void PermutationBoundaries::init_minimal_amount_vector(const int &amountofoperations)
{
	currentMinimalAmountToolChangesForCertainPermutationLength.reserve(amountofoperations);

	for (int i = 0; i < amountofoperations; i++) {
		currentMinimalAmountToolChangesForCertainPermutationLength.push_back(INT_MAX);
	}
}

bool PermutationBoundaries::node_is_candidate(const Permutation &permutation) const
{
	const long long AMOUNT_TOOL_CHANGES = permutation.calculate_tool_changes();
	const long long AMOUNT_OF_OPERATIONS = permutation.get_amount_of_operations();

	return (AMOUNT_TOOL_CHANGES <= currentMinimalAmountToolChangesForCertainPermutationLength[AMOUNT_OF_OPERATIONS - 1]);
}