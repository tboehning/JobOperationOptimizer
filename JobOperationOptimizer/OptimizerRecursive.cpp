#include "OptimizerRecursive.h"

OptimizerRecursive::OptimizerRecursive()
{
	optimalAmountOfToolChanges = INT_MAX;
	optimalLengthToolTransitions = INT_MAX;
}


void OptimizerRecursive::optimize_toolchanges()
{
	Permutation currentPermutation;
	
	std::set<JobOperation> decisionSet = decisionStacks.calculate_current_decision_set();
	
	for (const auto &decision : decisionSet) {
		check_node_toolchanges(currentPermutation, decisionStacks, decision);
	}
}

void OptimizerRecursive::check_node_toolchanges(Permutation permutationparent, DecisionStackList currentDecisionStackList, const JobOperation &decision)
{
	permutationparent.append_operation(decision);
	currentDecisionStackList.make_decision(decision);

	std::set<JobOperation> decisionSet = currentDecisionStackList.calculate_current_decision_set();

	if (decisionSet.empty()) {
		evaluate_leaf_toolchanges(permutationparent);
	}
	else {
		if (permutationparent.calculate_tool_changes() <= optimalAmountOfToolChanges) {
			for (const auto &decisionNew : decisionSet) {
				check_node_toolchanges(permutationparent, currentDecisionStackList, decisionNew);
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


void OptimizerRecursive::optimize_transitionlength()
{
	Permutation currentPermutation;
	
	std::set<JobOperation> decisionSet = decisionStacks.calculate_current_decision_set();
	
	for (const auto &decision : decisionSet) {
		check_node_length(currentPermutation, decisionStacks, decision);
	}
}

void OptimizerRecursive::check_node_length(Permutation permutationparent, DecisionStackList currentDecisionStackList, const JobOperation &decision)
{
	permutationparent.append_operation(decision);
	currentDecisionStackList.make_decision(decision);

	std::set<JobOperation> decisionSet = currentDecisionStackList.calculate_current_decision_set();

	if (decisionSet.empty()) {
		evaluate_leaf_length(permutationparent);
	}
	else {
		if (permutationparent.calculate_toolpath_from_transitions() < optimalLengthToolTransitions) {
			for (const auto &decisionNew : decisionSet) {
				check_node_length(permutationparent, currentDecisionStackList, decisionNew);
			}
		}
	}
}

void OptimizerRecursive::evaluate_leaf_length(const Permutation &permutation)
{
	const int AMOUNT_TOOL_CHANGES = permutation.calculate_tool_changes();
	const double LENGTH_TOOL_TRANSITIONS = permutation.calculate_toolpath_from_transitions();

	if (LENGTH_TOOL_TRANSITIONS < optimalLengthToolTransitions) {
		permutation.print_permutation();

		optimalAmountOfToolChanges = AMOUNT_TOOL_CHANGES;
		optimalLengthToolTransitions = LENGTH_TOOL_TRANSITIONS;
	}
	else if (abs(LENGTH_TOOL_TRANSITIONS - optimalLengthToolTransitions) < 0.01) {
		if (AMOUNT_TOOL_CHANGES < optimalAmountOfToolChanges) {
			permutation.print_permutation();

			optimalAmountOfToolChanges = AMOUNT_TOOL_CHANGES;
		}
	}
}


void OptimizerRecursive::append_ordered_joblist(const JobList &joblist)
{
	DecisionStack decisionStackInputJobList;

	for (int i = joblist.get_jobs().size() - 1; i >= 0; i--) {
		decisionStackInputJobList.append_operations_from_job(joblist.get_jobs()[i]);
	}

	decisionStacks.append_decision_stack_initial(decisionStackInputJobList);
}

void OptimizerRecursive::append_joblist_with_dependencies(const JobList &joblist)
{
	for (const auto &job : joblist.get_jobs()) {
		append_decisionstack_for_job(job);
	}
}

void OptimizerRecursive::print_decision_stacks() const
{
	decisionStacks.print_decision_stacks();
}

void OptimizerRecursive::append_decisionstack_for_job(const Job &job)
{
	DecisionStack stack;

	stack.append_operations_from_job(job);
	stack.append_dependencies_recursively_from_job(job);

	decisionStacks.append_decision_stack_initial(stack);
}