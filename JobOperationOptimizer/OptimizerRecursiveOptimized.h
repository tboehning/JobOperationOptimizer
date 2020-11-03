#ifndef OPTIMIZERRECURSIVEOPTIMIZED_H_
#define OPTIMIZERRECURSIVEOPTIMIZED_H_

#include "DecisionVectorList.h"
#include "Permutation.h"

class OptimizerRecursiveOptimized
{
public:
	OptimizerRecursiveOptimized();

	void optimize_toolchanges();

	void append_joblist(const JobList &joblist);

	void print_decision_stacks() const;

private:
	DecisionVectorList decisionVectors;
	std::vector<unsigned short> positions;
	std::vector<size_t> maxPositionPerVector;

	int optimalAmountOfToolChanges;
	double optimalLengthToolTransitions;

	int amountOfOperations;

	void check_node_toolchanges(Permutation permutationparent, std::vector<unsigned short> vectorpositions, const int &indexvector);
	void evaluate_leaf_toolchanges(const Permutation &permutation);

	bool next_decision_possible(const std::vector<unsigned short> &vectorpositions) const;
};

#endif