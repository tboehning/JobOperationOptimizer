#include "Optimizer.h"

Optimizer::Optimizer() 
{
	optimalAmountOfToolChanges = INT_MAX;
	optimalLengthToolTransitions = INT_MAX;
}

void Optimizer::optimize_toolchanges()
{
	Permutation currentPermutation;

	std::set<JobOperation> decisionSet = decisionStacksInitial.calculate_current_decision_set();

	for (const auto &decision : decisionSet) {
		check_node_toolchanges(currentPermutation, decisionStacksInitial, decision);
	}
}

void Optimizer::check_node_toolchanges(Permutation permutationparent, DecisionStackList currentDecisionStackList, const JobOperation &decision)
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

void Optimizer::evaluate_leaf_toolchanges(const Permutation &permutation)
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


void Optimizer::optimize_transition_length()
{
	Permutation currentPermutation;

	std::set<JobOperation> decisionSet = decisionStacksInitial.calculate_current_decision_set();

	for (const auto &decision : decisionSet) {
		check_node_length(currentPermutation, decisionStacksInitial, decision);
	}
}

void Optimizer::check_node_length(Permutation permutationparent, DecisionStackList currentDecisionStackList, const JobOperation &decision)
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

void Optimizer::evaluate_leaf_length(const Permutation &permutation)
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


void Optimizer::append_joblist(const JobList &list)
{
	for (const auto &job : list.get_jobs()) {
		append_job(job);
	}
}

void Optimizer::append_job(const Job &job)
{
	jobList.append_job(job);

	DecisionStack stack(job);
	decisionStacksInitial.append_decision_stack_initial(stack);
}

JobList Optimizer::get_jobs() const
{
	return jobList;
}

void Optimizer::print_decision_stacks() const
{
	decisionStacksInitial.print_decision_stacks();
}