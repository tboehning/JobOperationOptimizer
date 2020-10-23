//#ifndef OPTIMIZERGREEDY_H_
//#define OPTIMIZERGREEDY_H_
//
//#include "JobList.h"
//#include "DecisionStackList.h"
//
//class OptimizerGreedy
//{
//public:
//	OptimizerGreedy();
//
//	void optimize_toolchanges();
//
//	void append_ordered_joblist(const JobList &joblist);
//	void append_joblist_with_dependencies(const JobList &joblist);
//
//	void print_decision_stacks() const;
//
//private:
//	DecisionStackList decisionStacks;
//
//	int optimalAmountOfToolChanges;
//	double optimalLengthToolTransitions;
//
//	bool hasJobsWithUnorderedDependencies;
//
//	int amountOfOperations;
//
//	void append_decisionstack_for_job(const Job &job);
//
//	JobOperation calculate_next_best_decision(const Permutation &permutation, const std::set<JobOperation> &decisionset) const;
//};
//
//#endif