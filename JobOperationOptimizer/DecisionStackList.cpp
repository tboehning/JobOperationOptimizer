#include "DecisionStackList.h"

void DecisionStackList::append_decision_stack(const DecisionStack &stack)
{
	decisionStacks.push_back(stack);
}

std::vector<JobOperation> DecisionStackList::calculate_current_decision_set() const
{
	std::vector<JobOperation> decisionSet;

	for (const auto &decisionStack : decisionStacks) {
		if (!decisionStack.get_decisions().empty()) {
			if (std::find(decisionSet.begin(), decisionSet.end(), decisionStack.get_top()) == decisionSet.end()) {
				decisionSet.push_back(decisionStack.get_top());
			}
		}
	}

	return decisionSet;
}

void DecisionStackList::make_decision(const JobOperation &decision)
{
	made_decisions.push_back(decision);

	for (auto &stack : decisionStacks) {
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
	return decisionStacks;
}

void DecisionStackList::print_decision_stacks() const
{
	for (const auto &decisionstack : decisionStacks) {
		decisionstack.print_decisions();
	}
}

void DecisionStackList::pop_previous_decisions_from_stack(DecisionStack &decisionstack)
{
	if (!decisionstack.get_decisions().empty()) {
		while (std::find(made_decisions.begin(), made_decisions.end(), decisionstack.get_top()) != made_decisions.end()) {
			decisionstack.pop_top();
		}
	}
}
