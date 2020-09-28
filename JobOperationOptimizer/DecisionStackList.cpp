#include "DecisionStackList.h"

void DecisionStackList::append_decision_stack_initial(const DecisionStack &stack)
{
	decisionStacks.emplace_back(stack);
}

std::set<JobOperation> DecisionStackList::calculate_current_decision_set() const
{
	std::set<JobOperation> decisionSet;

	for (const auto &decisionStack : decisionStacks) {
		if (!decisionStack.get_decisions().empty()) {
			decisionSet.insert(decisionStack.get_top());
		}
	}

	return decisionSet;
}

void DecisionStackList::make_decision(const JobOperation &decision)
{
	for (auto &stack : decisionStacks) {
		if (!stack.get_decisions().empty()) {
			if (stack.get_top() == decision) {
				stack.pop_top();
			}
		}
	}
}

void DecisionStackList::pop_previous_decisions_from_stacks_top(const Permutation &permutation)
{
	for (auto &stack : decisionStacks) {
		if (!stack.get_decisions().empty()) {
			const std::vector<JobOperation> PREVIOUS_OPERATIONS = permutation.get_operations();

			while (std::find(PREVIOUS_OPERATIONS.begin(), PREVIOUS_OPERATIONS.end(), stack.get_top()) != PREVIOUS_OPERATIONS.end()) {
				stack.pop_top();
			}
		}
	}
}

std::vector<DecisionStack> DecisionStackList::get_decision_stacks() const
{
	return decisionStacks;
}

void DecisionStackList::print_decision_stacks() const
{
	for (const auto &decisionstack : decisionStacks) {
		decisionstack.print_decisions();
	}
}
