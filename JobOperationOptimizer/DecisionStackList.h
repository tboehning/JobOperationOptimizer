#ifndef DECISIONSTACKLIST_H_
#define DECISIONSTACKLIST_H_

#include <vector>
#include <set>

#include "DecisionStack.h"
#include "Permutation.h"

class DecisionStackList
{
public:
	void append_decision_stack_initial(const DecisionStack &stack);

	JobOperation pop_and_get_operation_from_stack(const int &position);

	int get_amount_of_stacks() const;
	std::vector<DecisionStack> get_decision_stacks() const;
	
	void print_decision_stacks() const;

private:
	std::vector<DecisionStack> decisionStacks;
};

#endif