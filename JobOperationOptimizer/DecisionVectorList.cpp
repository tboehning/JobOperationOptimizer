#include "DecisionVectorList.h"

void DecisionVectorList::append_decision_vector(const DecisionVector &vector)
{
	decisionVectors.push_back(vector);
}

void DecisionVectorList::append_joblist(const JobList &joblist)
{
	DecisionVector decisionVectorInputJobList;

	for (const auto &job : joblist.get_jobs()) {
		decisionVectorInputJobList.append_operations_from_job(job);
	}

	decisionVectors.push_back(decisionVectorInputJobList);
}

JobOperation DecisionVectorList::get_operation_at_position(const int &positionvector, const int &position) const
{
	return decisionVectors[positionvector].get_operation_at_position(position);
}

int DecisionVectorList::get_amount_of_vectors() const
{
	return decisionVectors.size();
}

void DecisionVectorList::print_decision_vectors() const
{
	for (const auto &vector : decisionVectors) {
		vector.print_decisions();
	}
}
