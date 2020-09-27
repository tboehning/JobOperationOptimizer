#ifndef OPTIMIZER_H_
#define OPTIMIZER_H_

#include "JobList.h"
#include "DecisionStackList.h"
#include "Permutation.h"

class Optimizer
{
public:
	Optimizer();

	void optimize_toolchanges();
	void optimize_transition_length();

	void append_joblist(const JobList &list);
	void append_job(const Job &job);

	JobList get_jobs() const;

	void print_decision_stacks() const;

private:
	JobList jobList;

	DecisionStackList decisionStacksInitial;

	int optimalAmountOfToolChanges;
	double optimalLengthToolTransitions;

	void check_node_toolchanges(Permutation permutationparent, DecisionStackList currentDecisionStackList, const JobOperation &decision);
	void check_node_length(Permutation permutationparent, DecisionStackList currentDecisionStackList, const JobOperation &decision);

	void evaluate_leaf_toolchanges(const Permutation &permutation);
	void evaluate_leaf_length(const Permutation &permutation);
};

#endif