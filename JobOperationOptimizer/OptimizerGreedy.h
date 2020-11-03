#ifndef OPTIMIZERGREEDY_H_
#define OPTIMIZERGREEDY_H_

#include "JobList.h"
#include "DecisionStackList.h"
#include "Permutation.h"

class OptimizerGreedy
{
public:
	OptimizerGreedy();

	void optimize_toolchanges();

	void append_joblist(const JobList &joblist);

	void print_decision_stacks() const;

private:
	DecisionStackList decisionStacks;

	int optimalAmountOfToolChanges;
	double optimalLengthToolTransitions;

	int amountOfOperations;

	void append_decisionstack_for_job(const Job &job);

	std::vector<JobOperation> calculate_decision_set() const;
	JobOperation calculate_next_best_decision(const Permutation &permutation, const std::vector<JobOperation> &possibledecisions) const;
};

#endif