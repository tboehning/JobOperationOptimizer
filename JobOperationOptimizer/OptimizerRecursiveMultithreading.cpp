#include "OptimizerRecursiveMultithreading.h"

OptimizerRecursiveMultithreading::OptimizerRecursiveMultithreading()
{
	optimalAmountOfOperations = INT_MAX;

	amountOfOperations = 0;
}

Permutation OptimizerRecursiveMultithreading::optimize_toolchanges()
{
	Permutation startPermutation(amountOfOperations);
	std::vector<std::future<Permutation>> futurePermutations;

	for (int i = 0; i <= decisionStacks.get_amount_of_stacks() - 1; ++i) {
		futurePermutations.push_back(std::async(&OptimizerRecursiveMultithreading::get_best_permutation_for_toolchanges_from_subtree, this, startPermutation, decisionStacks, i));
	}

	std::vector<Permutation> bestPermutationsFromSubtrees = get_all_future_permutations(futurePermutations);

	return find_best_permutation_for_toolchanges_from_permutations(bestPermutationsFromSubtrees);
}

Permutation OptimizerRecursiveMultithreading::get_best_permutation_for_toolchanges_from_subtree(Permutation permutationparent, DecisionStackList currentDecisionStackList, const int &indexstack)
{
	permutationparent.append_operation(currentDecisionStackList.pop_and_get_operation_from_stack(indexstack));

	if (permutationparent.calculate_tool_changes() <= optimalAmountOfOperations) {
		if (currentDecisionStackList.get_decision_stacks().empty()) {
			return permutationparent;
		}
		else {
			std::vector<Permutation> permutationsFromSubtrees;

			for (int i = 0; i <= currentDecisionStackList.get_amount_of_stacks() - 1; ++i) {
				permutationsFromSubtrees.push_back(get_best_permutation_for_toolchanges_from_subtree(permutationparent, currentDecisionStackList, i));
			}

			return find_best_permutation_for_toolchanges_from_permutations(permutationsFromSubtrees);
		}
	}
	else {
		return Permutation(amountOfOperations);
	}
}

Permutation OptimizerRecursiveMultithreading::find_best_permutation_for_toolchanges_from_permutations(std::vector<Permutation> &permutations)
{
	Permutation bestPermutation(amountOfOperations);

	bool firstValidPermutationFound = false;

	for (int i = 0; i < permutations.size(); i++) {
		if (permutations[i].get_amount_of_operations() > 0) {
			if (!firstValidPermutationFound) {
				bestPermutation = permutations[i];

				firstValidPermutationFound = true;

				continue;
			}

			Permutation currentPermutation = permutations[i];

			const int AMOUNT_TOOL_CHANGES_CURRENT_PERMUTATION = currentPermutation.calculate_tool_changes();
			const double LENGTH_TOOL_TRANSITIONS_CURRENT_PERMUTATION = currentPermutation.calculate_toolpath_from_transitions();

			if (AMOUNT_TOOL_CHANGES_CURRENT_PERMUTATION < bestPermutation.calculate_tool_changes()) {
				bestPermutation = currentPermutation;
			}
			else if (AMOUNT_TOOL_CHANGES_CURRENT_PERMUTATION == bestPermutation.calculate_tool_changes()) {
				if (LENGTH_TOOL_TRANSITIONS_CURRENT_PERMUTATION < bestPermutation.calculate_toolpath_from_transitions()) {
					bestPermutation = currentPermutation;
				}
			}
		}
	}

	{
		std::lock_guard<std::mutex> lockGuard(mutex);

		if (bestPermutation.get_amount_of_operations() == amountOfOperations
			&& bestPermutation.calculate_tool_changes() < optimalAmountOfOperations) {
			optimalAmountOfOperations = bestPermutation.calculate_tool_changes();
		}
	}
	

	return bestPermutation;
}

std::vector<Permutation> OptimizerRecursiveMultithreading::get_all_future_permutations(std::vector<std::future<Permutation>> &futurepermutations) const
{
	std::vector<Permutation> gottenPermutations;

	for (auto &futurePermutation : futurepermutations) {
		gottenPermutations.push_back(futurePermutation.get());
	}

	return gottenPermutations;
}

void OptimizerRecursiveMultithreading::append_joblist(const JobList &joblist)
{
	amountOfOperations += joblist.get_amount_of_operations();

	DecisionStack decisionStackInputJobList;

	for (int i = joblist.get_jobs().size() - 1; i >= 0; i--) {
		decisionStackInputJobList.append_operations_from_job(joblist.get_jobs()[i]);
	}

	decisionStacks.append_decision_stack_initial(decisionStackInputJobList);
}

void OptimizerRecursiveMultithreading::print_decision_stacks() const
{
	decisionStacks.print_decision_stacks();
}

void OptimizerRecursiveMultithreading::append_decisionstack_for_job(const Job &job)
{
	DecisionStack stack;

	stack.append_operations_from_job(job);

	decisionStacks.append_decision_stack_initial(stack);
}