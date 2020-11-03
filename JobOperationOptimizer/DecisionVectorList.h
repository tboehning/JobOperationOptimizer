#ifndef DECISIONVECTORLIST_H_
#define DECISIONVECTORLIST_H_

#include "DecisionVector.h"

class DecisionVectorList
{
public:
	void append_decision_vector(const DecisionVector &vector);
	void append_joblist(const JobList &joblist);

	JobOperation get_operation_at_position(const int &positionvector, const int &position) const;

	int get_amount_of_vectors() const;

	void print_decision_vectors() const;

private:
	std::vector<DecisionVector> decisionVectors;
};

#endif