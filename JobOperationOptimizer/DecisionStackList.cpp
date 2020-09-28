#include "DecisionStackList.h"

void DecisionStackList::append_decision_stack_initial(const DecisionStack &stack)
{
	decisionStacksInitial.emplace_back(stack);
}

std::set<JobOperation> DecisionStackList::calculate_current_decision_set() const
{
	std::set<JobOperation> decisionSet;

	for (const auto &decisionStack : decisionStacksInitial) {
		if (!decisionStack.get_decisions().empty()) {
			decisionSet.insert(decisionStack.get_top());
		}
	}

	return decisionSet;
}

void DecisionStackList::make_decision(const JobOperation &decision)
{
	previous_decisions.emplace_back(decision);

	for (auto &stack : decisionStacksInitial) {
		if (!stack.get_decisions().empty()) {
			if (stack.get_top() == decision) {
				stack.pop_top();
			}

			pop_previous_decisions_from_stack(stack);
		}
	}
}

std::vector<DecisionStack> DecisionStackList::get_decision_stacks() const
{
	return decisionStacksInitial;
}

void DecisionStackList::print_decision_stacks() const
{
	for (const auto &decisionstack : decisionStacksInitial) {
		decisionstack.print_decisions();
	}
}

void DecisionStackList::pop_previous_decisions_from_stack(DecisionStack &decisionstack)
{
	if (!decisionstack.get_decisions().empty()) {
		while (std::find(previous_decisions.begin(), previous_decisions.end(), decisionstack.get_top()) != previous_decisions.end()) {
			decisionstack.pop_top();
		}
	}
}
