#include "OptimizerRecursiveOptimized.h"

OptimizerRecursiveOptimized::OptimizerRecursiveOptimized()
{
	optimalAmountOfToolChanges = INT_MAX;
	optimalLengthToolTransitions = INT_MAX;

	amountOfOperations = 0;
}

void OptimizerRecursiveOptimized::optimize_toolchanges()
{
	PermutationPointer currentPermutation(amountOfOperations);
	std::vector<std::thread> threads;

	for (int i = 0; i <= decisionVectors.get_amount_of_vectors() - 1; ++i) {
		threads.push_back(std::thread(&OptimizerRecursiveOptimized::check_node_toolchanges, this, currentPermutation, positions, i));
		//check_node_toolchanges(currentPermutation, positions, i);
	}

	for (auto &t : threads) {
		t.join();
	}
}

void OptimizerRecursiveOptimized::check_node_toolchanges(PermutationPointer permutationparent, std::vector<unsigned short> vectorpositions, const int &indexvector)
{
	permutationparent.append_operation(decisionVectors.get_operation_at_position(indexvector, vectorpositions[indexvector]));
	++vectorpositions[indexvector];

	if (!next_decision_possible(vectorpositions)) {
		evaluate_leaf_toolchanges(permutationparent);
	}
	else {
		if (permutationparent.calculate_tool_changes() <= optimalAmountOfToolChanges) {
			for (int i = 0; i <= decisionVectors.get_amount_of_vectors() - 1; ++i) {
				if (vectorpositions[i] <= maxPositionPerVector[i]) {
					check_node_toolchanges(permutationparent, vectorpositions, i);
				}
			}
		}
	}
}

bool OptimizerRecursiveOptimized::next_decision_possible(const std::vector<unsigned short> &vectorpositions) const
{
	for (int i = 0; i <= vectorpositions.size() - 1; ++i) {
		if (vectorpositions[i] <= maxPositionPerVector[i]) {
			return true;
		}
	}

	return false;
}

void OptimizerRecursiveOptimized::evaluate_leaf_toolchanges(const PermutationPointer &permutation)
{
	const int AMOUNT_TOOL_CHANGES = permutation.calculate_tool_changes();
	const double LENGTH_TOOL_TRANSITIONS = permutation.calculate_toolpath_from_transitions();

	{
		std::lock_guard<std::mutex> lockGuard(updateOptimalValuesMutex);

		if (AMOUNT_TOOL_CHANGES < optimalAmountOfToolChanges) {
			permutation.print_permutation();

			optimalAmountOfToolChanges = AMOUNT_TOOL_CHANGES;
			optimalLengthToolTransitions = LENGTH_TOOL_TRANSITIONS;
		}
		else if (AMOUNT_TOOL_CHANGES == optimalAmountOfToolChanges) {
			if (LENGTH_TOOL_TRANSITIONS < optimalLengthToolTransitions) {
				permutation.print_permutation();

				optimalLengthToolTransitions = LENGTH_TOOL_TRANSITIONS;
			}
		}
	}
}

void OptimizerRecursiveOptimized::append_joblist(const JobList &joblist)
{
	amountOfOperations += joblist.get_amount_of_operations();
	positions.push_back(0);
	maxPositionPerVector.push_back(joblist.get_amount_of_operations() - 1);

	decisionVectors.append_joblist(joblist);
}

void OptimizerRecursiveOptimized::print_decision_stacks() const
{
	decisionVectors.print_decision_vectors();
}