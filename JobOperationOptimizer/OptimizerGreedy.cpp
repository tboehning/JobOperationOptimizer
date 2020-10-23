#include "OptimizerGreedy.h"

OptimizerGreedy::OptimizerGreedy()
{
	optimalAmountOfToolChanges = INT_MAX;
	optimalLengthToolTransitions = INT_MAX;

	amountOfOperations = 0;
}

void OptimizerGreedy::optimize_toolchanges()
{
	Permutation currentPermutation(amountOfOperations);

	for (int i = 0; i <= amountOfOperations - 1; i++) {
		std::vector<JobOperation> possibleDecisions = calculate_decision_set();

		JobOperation decision = calculate_next_best_decision(currentPermutation, possibleDecisions);

		currentPermutation.append_operation(decision);

		for (int i = 0; i <= decisionStacks.get_amount_of_stacks() - 1; ++i) {
			if (decisionStacks.get_decision_stacks()[i].get_top() == decision) {
				decisionStacks.pop_and_get_operation_from_stack(i);
			}
		}
	}

	currentPermutation.print_permutation();
}

void OptimizerGreedy::append_joblist(const JobList &joblist)
{
	amountOfOperations += joblist.get_amount_of_operations();

	DecisionStack decisionStackInputJobList;

	for (int i = joblist.get_jobs().size() - 1; i >= 0; i--) {
		decisionStackInputJobList.append_operations_from_job(joblist.get_jobs()[i]);
	}

	decisionStacks.append_decision_stack_initial(decisionStackInputJobList);
}

void OptimizerGreedy::print_decision_stacks() const
{
	decisionStacks.print_decision_stacks();
}

void OptimizerGreedy::append_decisionstack_for_job(const Job &job)
{
	DecisionStack stack;

	stack.append_operations_from_job(job);

	decisionStacks.append_decision_stack_initial(stack);
}

std::vector<JobOperation> OptimizerGreedy::calculate_decision_set() const
{
	std::vector<JobOperation> decisionSet;

	for (int i = 0; i <= decisionStacks.get_amount_of_stacks() - 1; ++i) {
		decisionSet.push_back(decisionStacks.get_decision_stacks()[i].get_top());
	}

	return decisionSet;
 }

JobOperation OptimizerGreedy::calculate_next_best_decision(const Permutation &permutation, const std::vector<JobOperation> &possibledecisions) const
{
	JobOperation firstBestDecision;
	JobOperation secondBestDecision;

	int previousOperationToolnumber;
	Vector previousOperationEndpoint;

	double currentBestLengthFirstBestDecision = INT_MAX;
	double currentBestLengthSecondBestDecision = INT_MAX;

	bool operationWithZeroToolchangesFound = false;

	if (permutation.get_operations().empty()) {
		previousOperationToolnumber = INT_MIN;
		previousOperationEndpoint = Vector(0.0, 0.0, 0.0);
	}
	else {
		previousOperationToolnumber = permutation.get_operations().back().toolNumber;
		previousOperationEndpoint = permutation.get_operations().back().endPosition;
	}
	
	for (const auto &possibleDecision : possibledecisions) {
		const int TOOLCHANGES_POSSIBLE_DECISION = (previousOperationToolnumber == possibleDecision.toolNumber) ? 0 : 1;
		const double LENGTH_TRANSITION_POSSIBLE_DECISION = previousOperationEndpoint.calculate_distance_to_vector(possibleDecision.startPosition);

		if (TOOLCHANGES_POSSIBLE_DECISION == 0) {
			operationWithZeroToolchangesFound = true;

			if (LENGTH_TRANSITION_POSSIBLE_DECISION < currentBestLengthFirstBestDecision) {
				firstBestDecision = possibleDecision;

				currentBestLengthFirstBestDecision = LENGTH_TRANSITION_POSSIBLE_DECISION;
			}
		}
		else if (!operationWithZeroToolchangesFound) {
			if (LENGTH_TRANSITION_POSSIBLE_DECISION < currentBestLengthSecondBestDecision) {
				secondBestDecision = possibleDecision;

				currentBestLengthSecondBestDecision = LENGTH_TRANSITION_POSSIBLE_DECISION;
			}
		}
	}

	return (operationWithZeroToolchangesFound) ? firstBestDecision : secondBestDecision;
}