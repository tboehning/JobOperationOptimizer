#include "Optimizer.h"

Optimizer::Optimizer() 
{
	optimalAmountOfToolChanges = INT_MAX;
	optimalLengthToolTransitions = INT_MAX;
}

void Optimizer::optimize_toolchanges()
{
	Permutation currentPermutation;

	std::vector<JobOperation> decisionSet = decisionStacksInitial.calculate_current_decision_set();

	for (const auto &decision : decisionSet) {
		optimize_recursive_toolchanges(currentPermutation, decisionStacksInitial, decision);
	}
}

void Optimizer::optimize_transition_length()
{
	Permutation currentPermutation;

	std::vector<JobOperation> decisionSet = decisionStacksInitial.calculate_current_decision_set();

	for (const auto &decision : decisionSet) {
		optimize_recursive_length(currentPermutation, decisionStacksInitial, decision);
	}
}

void Optimizer::optimize_recursive_toolchanges(Permutation permutationparent, DecisionStackList currentDecisionStackList, const JobOperation decision)
{
	permutationparent.append_operation(decision);
	currentDecisionStackList.make_decision(decision);

	std::vector<JobOperation> decisionSet = currentDecisionStackList.calculate_current_decision_set();

	if (decisionSet.empty()) {
		check_current_leaf_toolchanges(permutationparent);
	}
	else {
		for (const auto &decisionNew : decisionSet) {
			optimize_recursive_toolchanges(permutationparent, currentDecisionStackList, decisionNew);
		}
	}
}

void Optimizer::optimize_recursive_length(Permutation permutationparent, DecisionStackList currentDecisionStackList, const JobOperation decision)
{
	permutationparent.append_operation(decision);
	currentDecisionStackList.make_decision(decision);

	std::vector<JobOperation> decisionSet = currentDecisionStackList.calculate_current_decision_set();

	if (decisionSet.empty()) {
		check_current_leaf_length(permutationparent);
	}
	else {
		for (const auto &decisionNew : decisionSet) {
			optimize_recursive_length(permutationparent, currentDecisionStackList, decisionNew);
		}
	}
}

void Optimizer::check_current_leaf_toolchanges(const Permutation &permutation)
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

void Optimizer::check_current_leaf_length(const Permutation &permutation)
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

void Optimizer::append_job(const Job &job)
{
	jobList.append_job(job);

	DecisionStack stack(job);
	decisionStacksInitial.append_decision_stack(stack);
}

JobList Optimizer::get_jobs() const
{
	return jobList;
}

void Optimizer::print_decision_stacks() const
{
	decisionStacksInitial.print_decision_stacks();
}


