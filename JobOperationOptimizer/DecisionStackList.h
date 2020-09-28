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

	std::set<JobOperation> calculate_current_decision_set() const;

	void make_decision(const JobOperation &decision);

	void pop_previous_decisions_from_stacks_top(const Permutation &permutation);

	std::vector<DecisionStack> get_decision_stacks() const;

	void print_decision_stacks() const;

private:
	std::vector<DecisionStack> decisionStacks;
};

#endif