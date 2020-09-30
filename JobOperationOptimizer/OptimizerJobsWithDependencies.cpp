#include "OptimizerJobsWithDependencies.h"

OptimizerJobsWithDependencies::OptimizerJobsWithDependencies()
{
	optimalAmountOfToolChanges = INT_MAX;
	optimalLengthToolTransitions = INT_MAX;
}

void OptimizerJobsWithDependencies::optimize_toolchanges()
{
	Permutation currentPermutation;

	std::set<JobOperation> decisionSet = decisionStacks.calculate_current_decision_set();

	for (const auto &decision : decisionSet) {
		check_node_toolchanges(currentPermutation, decisionStacks, decision);
	}
}

void OptimizerJobsWithDependencies::check_node_toolchanges(Permutation permutationparent, DecisionStackList currentDecisionStackList, const JobOperation &decision)
{
	permutationparent.append_operation(decision);
	currentDecisionStackList.make_decision(decision);
	currentDecisionStackList.pop_previous_decisions_from_stacks_top(permutationparent);

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

void OptimizerJobsWithDependencies::evaluate_leaf_toolchanges(const Permutation &permutation)
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


void OptimizerJobsWithDependencies::optimize_transition_length()
{
	Permutation currentPermutation;

	std::set<JobOperation> decisionSet = decisionStacks.calculate_current_decision_set();

	for (const auto &decision : decisionSet) {
		check_node_length(currentPermutation, decisionStacks, decision);
	}
}

void OptimizerJobsWithDependencies::check_node_length(Permutation permutationparent, DecisionStackList currentDecisionStackList, const JobOperation &decision)
{
	permutationparent.append_operation(decision);
	currentDecisionStackList.make_decision(decision);
	currentDecisionStackList.pop_previous_decisions_from_stacks_top(permutationparent);

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

void OptimizerJobsWithDependencies::evaluate_leaf_length(const Permutation &permutation)
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


void OptimizerJobsWithDependencies::append_joblist(const JobList &list)
{
	for (const auto &job : list.get_jobs()) {
		append_job(job);
	}
}

void OptimizerJobsWithDependencies::append_job(const Job &job)
{
	jobList.append_job(job);

	DecisionStack stack;
	stack.append_operations_from_job(job);
	stack.append_dependencies_recursively_from_job(job);
	decisionStacks.append_decision_stack_initial(stack);
}

JobList OptimizerJobsWithDependencies::get_jobs() const
{
	return jobList;
}

void OptimizerJobsWithDependencies::print_decision_stacks() const
{
	decisionStacks.print_decision_stacks();
}