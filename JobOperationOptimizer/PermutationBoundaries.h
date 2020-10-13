#ifndef PERMUTATIONBOUNDARIES_H_
#define PERMUTATIONBOUNDARIES_H_

#include <mutex>
#include <vector>

#include "Permutation.h"

class PermutationBoundaries
{
public:
	PermutationBoundaries();
	PermutationBoundaries(const int &amountofoperations);

	void init_minimal_amount_vector(const int &amountofoperations);

	bool node_is_candidate(const Permutation &permutation) const;

	void check_and_update_minimal_amount_vector(const Permutation &bestpermutationnode);

	void print_vector() const;

private:
	std::mutex vectorMutex;

	std::vector<int> currentMinimalAmountToolChangesForCertainPermutationLength;
};

#endif