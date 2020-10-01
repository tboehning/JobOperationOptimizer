#ifndef OPTIMIZERRECURSIVE_H_
#define OPTIMIZERRECURSIVE_H_

#include "DecisionStackList.h"

class OptimizerRecursive
{
public:
	OptimizerRecursive();

	void optimize_toolchanges();
	void optimize_transitionlength();

	void append_ordered_joblist(const JobList &joblist);
	void append_joblist_with_dependencies(const JobList &joblist);

	void print_decision_stacks() const;

private:
	DecisionStackList decisionStacks;

	int optimalAmountOfToolChanges;
	double optimalLengthToolTransitions;

	bool hasJobsWithUnorderedDependencies;

	void append_decisionstack_for_job(const Job &job);

	void check_node_toolchanges(Permutation permutationparent, DecisionStackList currentDecisionStackList, const JobOperation &decision);
	void evaluate_leaf_toolchanges(const Permutation &permutation);

	void check_node_length(Permutation permutationparent, DecisionStackList currentDecisionStackList, const JobOperation &decision);
	void evaluate_leaf_length(const Permutation &permutation);
};

#endif