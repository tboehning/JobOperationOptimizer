#include "OptimizerRecursive.h"

OptimizerRecursive::OptimizerRecursive()
{
	optimalAmountOfToolChanges = INT_MAX;
	optimalLengthToolTransitions = INT_MAX;

	amountOfOperations = 0;
}


void OptimizerRecursive::optimize_toolchanges()
{
	Permutation currentPermutation(amountOfOperations);

	for (int i = 0; i <= decisionStacks.get_amount_of_stacks() - 1; ++i) {
		check_node_toolchanges(currentPermutation, decisionStacks, i);
	}
}

void OptimizerRecursive::check_node_toolchanges(Permutation permutationparent, DecisionStackList currentDecisionStackList, const int &indexstack)
{
	permutationparent.append_operation(currentDecisionStackList.pop_and_get_operation_from_stack(indexstack));

	if (currentDecisionStackList.get_decision_stacks().empty()) {
		evaluate_leaf_toolchanges(permutationparent);
	}
	else {
		if (permutationparent.calculate_tool_changes() <= optimalAmountOfToolChanges) {
			for (int i = 0; i <= currentDecisionStackList.get_amount_of_stacks() - 1; ++i) {
				check_node_toolchanges(permutationparent, currentDecisionStackList, i);
			}
		}
	}
}

void OptimizerRecursive::evaluate_leaf_toolchanges(const Permutation &permutation)
{
	const int AMOUNT_TOOL_CHANGES = permutation.calculate_tool_changes();
	const double LENGTH_TOOL_TRANSITIONS = permutation.calculate_toolpath_from_transitions();

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

void OptimizerRecursive::append_joblist(const JobList &joblist)
{
	amountOfOperations += joblist.get_amount_of_operations();

	DecisionStack decisionStackInputJobList;

	for (int i = joblist.get_jobs().size() - 1; i >= 0; --i) {
		decisionStackInputJobList.append_operations_from_job(joblist.get_jobs()[i]);
	}

	decisionStacks.append_decision_stack_initial(decisionStackInputJobList);
}

void OptimizerRecursive::print_decision_stacks() const
{
	decisionStacks.print_decision_stacks();
}