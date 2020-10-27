#include "OptimizerGrouping.h"

void OptimizerGrouping::append_joblist(const JobList &joblist)
{
	jobLists.push_back(joblist);

	if (jobLists.size() > 1) {
		highestAllowedPositionToInsertPerJoblist.push_back(0);
	}
}

void OptimizerGrouping::optimize_toolchanges()
{
	init_groups(jobLists[0]);

	for (int i = 1; i <= jobLists.size() - 1; ++i) {
		firstInsertionPointFound = false;

		add_joblist_to_groups(jobLists[i]);
	}

	after_grouping(groupList);
	currentBestSolution = groupList;

	after_optimizing();

	currentBestSolution.print_groups();
}


void OptimizerGrouping::print_groups() const
{
	groupList.print_groups();
}

void OptimizerGrouping::init_groups(const JobList &joblist)
{
	for (int indexJob = 0; indexJob <= joblist.get_amount_of_jobs() - 1; ++indexJob) {
		for (int indexOperation = 0; indexOperation <= joblist.get_jobs()[indexJob].get_amount_of_operations() - 1; ++indexOperation) {
			if ((indexJob == 0 && indexOperation == 0) 
				|| joblist.get_jobs()[indexJob].get_operations()[indexOperation].toolNumber != groupList.get_toolnumber_of_last_group()) {

				groupList.create_group_with_operation_at_end(joblist.get_jobs()[indexJob].get_operations()[indexOperation]);
			}
			else {
				groupList.add_operation_to_last_group(joblist.get_jobs()[indexJob].get_operations()[indexOperation]);
			}
		}
	}
}

void OptimizerGrouping::add_joblist_to_groups(const JobList &joblist)
{
	for (const auto &job : joblist.get_jobs()) {
		for (const auto &operation : job.get_operations()) {
			add_operation_to_groups(operation);
		}
	}
}

void OptimizerGrouping::add_operation_to_groups(const JobOperation &operation)
{
	const long long OPERATION_LIST_NUMBER = operation.listNumber;
	const int OPERATION_TOOL_NUMBER = operation.toolNumber;
	const long long HIGHEST_POSSIBLE_POSITION = highestAllowedPositionToInsertPerJoblist[OPERATION_LIST_NUMBER - 2];

	if (groupList.get_toolnumber_at_position(HIGHEST_POSSIBLE_POSITION) == OPERATION_TOOL_NUMBER) {
		groupList.add_operation_to_position_at_end(operation, HIGHEST_POSSIBLE_POSITION);

		firstInsertionPointFound = true;
	}
	else if (HIGHEST_POSSIBLE_POSITION > 0 
		&& HIGHEST_POSSIBLE_POSITION + 1 <= groupList.get_amount_of_groups() - 1
		&& groupList.get_toolnumber_at_position(HIGHEST_POSSIBLE_POSITION + 1) == OPERATION_TOOL_NUMBER) {

		groupList.add_operation_to_position_at_end(operation, HIGHEST_POSSIBLE_POSITION + 1);
		++highestAllowedPositionToInsertPerJoblist[OPERATION_LIST_NUMBER - 2];

		firstInsertionPointFound = true;
	}
	else {
		add_new_group_at_next_position_for_joblist(operation);
	}
}

void OptimizerGrouping::add_new_group_at_next_position_for_joblist(const JobOperation &operation)
{
	const long long OPERATION_LIST_NUMBER = operation.listNumber;
	const int HIGHEST_POSSIBLE_POSITION = highestAllowedPositionToInsertPerJoblist[OPERATION_LIST_NUMBER - 2];

	int offsetIndex = 0;

	if (firstInsertionPointFound) {
		offsetIndex = 1;

		++highestAllowedPositionToInsertPerJoblist[OPERATION_LIST_NUMBER - 2];
	}

	groupList.create_group_with_operation_at_position(operation, HIGHEST_POSSIBLE_POSITION + offsetIndex);

	firstInsertionPointFound = true;
}


void OptimizerGrouping::after_grouping(OperationsGroupList &groups)
{
	BackwardGrouper grouper(groups);
	grouper.group();

	groups = grouper.get_groups();
}

void OptimizerGrouping::after_grouping(OperationsGroupList &groups, const int &lowestlimitgroup)
{
	BackwardGrouper grouper(groups, lowestlimitgroup);
	grouper.group();

	groups = grouper.get_groups();
}

void OptimizerGrouping::after_optimizing()
{
	for (int indexGroup = groupList.get_amount_of_groups() - 2; indexGroup >= 0; --indexGroup) {
		const int AMOUNT_OF_OPERATIONS_IN_GROUP = groupList.get_amount_of_operations_for_group(indexGroup);

		if (AMOUNT_OF_OPERATIONS_IN_GROUP >= 2) {
			for (int indexOperation = AMOUNT_OF_OPERATIONS_IN_GROUP - 1; indexOperation >= 0; --indexOperation) {
				const int LOWEST_POSITION_POSSIBLE = groupList.find_lowest_position_possible(indexGroup, indexOperation);

				if (LOWEST_POSITION_POSSIBLE > indexGroup + 1) {
					OperationsGroupList groupListAlternativeSolution = groupList;
					groupListAlternativeSolution.move_operation_and_create_new_group(indexGroup, indexOperation, LOWEST_POSITION_POSSIBLE);

					after_grouping(groupListAlternativeSolution, LOWEST_POSITION_POSSIBLE);

					if (groupListAlternativeSolution.get_amount_of_groups() < currentBestSolution.get_amount_of_groups()) {
						currentBestSolution = groupListAlternativeSolution;
					}
				}
			}
		}
	}
}