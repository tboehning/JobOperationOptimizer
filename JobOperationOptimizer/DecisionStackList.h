#ifndef DECISIONSTACKLIST_H_
#define DECISIONSTACKLIST_H_

#include <vector>

#include "DecisionStack.h"
#include "JobOperation.h"

class DecisionStackList
{
public:
	void append_decision_stack(const DecisionStack &stack);

	std::vector<JobOperation> calculate_current_decision_set() const;
	void make_decision(const JobOperation &decision);

	std::vector<DecisionStack> get_decision_stacks() const;

	void print_decision_stacks() const;

private:
	std::vector<DecisionStack> decisionStacks;
	std::vector<JobOperation> made_decisions;

	void pop_previous_decisions_from_stack(DecisionStack &decisionstack);
};

#endif