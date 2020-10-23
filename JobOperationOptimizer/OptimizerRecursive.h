#ifndef OPTIMIZERRECURSIVE_H_
#define OPTIMIZERRECURSIVE_H_

#include "DecisionStackList.h"

class OptimizerRecursive
{
public:
	OptimizerRecursive();

	void optimize_toolchanges();

	void append_joblist(const JobList &joblist);

	void print_decision_stacks() const;

private:
	DecisionStackList decisionStacks;

	int optimalAmountOfToolChanges;
	double optimalLengthToolTransitions;

	int amountOfOperations;

	void check_node_toolchanges(Permutation permutationparent, DecisionStackList currentDecisionStackList, const int &indexstack);
	void evaluate_leaf_toolchanges(const Permutation &permutation);
};

#endif