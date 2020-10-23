#include "DecisionStackList.h"

void DecisionStackList::append_decision_stack_initial(const DecisionStack &stack)
{
	decisionStacks.emplace_back(stack);
}

JobOperation DecisionStackList::pop_and_get_operation_from_stack(const int &position)
{
	JobOperation operation = decisionStacks[position].get_top();

	decisionStacks[position].pop_top();

	if (decisionStacks[position].is_empty()) {
		decisionStacks.erase(decisionStacks.begin() + position);
	}

	return operation;
}

std::vector<DecisionStack> DecisionStackList::get_decision_stacks() const
{
	return decisionStacks;
}

int DecisionStackList::get_amount_of_stacks() const
{
	return decisionStacks.size();
}

void DecisionStackList::print_decision_stacks() const
{
	for (const auto &decisionstack : decisionStacks) {
		decisionstack.print_decisions();
	}
}
