#ifndef OPTIMIZERRECURSIVEMULTITHREADING_H_
#define OPTIMIZERRECURSIVEMULTITHREADING_H_

#include <future>
#include <mutex>

#include "DecisionStackList.h"
#include "Permutation.h"

class OptimizerRecursiveMultithreading
{
public:
	OptimizerRecursiveMultithreading();

	Permutation optimize_toolchanges();

	void append_joblist(const JobList &joblist);

	void print_decision_stacks() const;

private:
	DecisionStackList decisionStacks;

	int amountOfOperations;
	int optimalAmountOfOperations;

	std::mutex mutex;

	void append_decisionstack_for_job(const Job &job);

	Permutation get_best_permutation_for_toolchanges_from_subtree(Permutation permutationparent, DecisionStackList currentDecisionStackList, const int &indexstack);
	Permutation find_best_permutation_for_toolchanges_from_permutations(std::vector<Permutation> &permutations);

	std::vector<Permutation> get_all_future_permutations(std::vector<std::future<Permutation>> &futurepermutations) const;

};

#endif