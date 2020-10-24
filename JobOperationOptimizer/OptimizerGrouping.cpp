#include "OptimizerGrouping.h"

void OptimizerGrouping::append_ordered_joblist(const JobList &joblist)
{
	jobLists.push_back(joblist);

	if (jobLists.size() > 1) {
		highestAllowedPositionToInsertPerJoblist.push_back(0);
	}
}

void OptimizerGrouping::optimize_toolchanges()
{
	for (int i = 0; i < jobLists.size(); ++i) {
		firstInsertionPointFound = false;

		if (i == 0) {
			init_groups(jobLists[i]);

			continue;
		}
		add_joblist_to_list(jobLists[i]);
	}

	after_grouping();
}

void OptimizerGrouping::print_groups() const
{
	for (const auto &group : operationsGroups) {
		group.print_group();
	}
}

void OptimizerGrouping::init_groups(const JobList &joblist)
{
	for (const auto &job : joblist.get_jobs()) {
		for (const auto &operation : job.get_operations()) {
			OperationsGroup group(operation.toolNumber);
			group.add_operation(operation);

			operationsGroups.push_back(group);
		}
	}
}

void OptimizerGrouping::add_joblist_to_list(const JobList &joblist)
{
	for (const auto &job : joblist.get_jobs()) {
		for (const auto &operation : job.get_operations()) {
			add_operation_to_list(operation);
		}
	}
}

void OptimizerGrouping::add_operation_to_list(const JobOperation &operation)
{
	const long long OPERATION_LIST_NUMBER = operation.listNumber;
	const int OPERATION_TOOL_NUMBER = operation.toolNumber;
	const long long HIGHEST_POSSIBLE_POSITION = highestAllowedPositionToInsertPerJoblist[OPERATION_LIST_NUMBER - 2];

	if (operationsGroups[HIGHEST_POSSIBLE_POSITION].get_toolnumber() == OPERATION_TOOL_NUMBER) {
		operationsGroups[HIGHEST_POSSIBLE_POSITION].add_operation(operation);

		firstInsertionPointFound = true;
	}
	else if ((HIGHEST_POSSIBLE_POSITION + 1) < operationsGroups.size()
		&& operationsGroups[HIGHEST_POSSIBLE_POSITION + 1].get_toolnumber() == OPERATION_TOOL_NUMBER) {
		operationsGroups[HIGHEST_POSSIBLE_POSITION + 1].add_operation(operation);
		++highestAllowedPositionToInsertPerJoblist[OPERATION_LIST_NUMBER - 2];

		firstInsertionPointFound = true;
	}
	else {
		add_new_group(operation);
	}
}

void OptimizerGrouping::add_new_group(const JobOperation &operation)
{
	const long long OPERATION_LIST_NUMBER = operation.listNumber;
	const int OPERATION_TOOL_NUMBER = operation.toolNumber;
	const int HIGHEST_POSSIBLE_POSITION = highestAllowedPositionToInsertPerJoblist[OPERATION_LIST_NUMBER - 2];

	OperationsGroup group(OPERATION_TOOL_NUMBER);
	group.add_operation(operation);

	int offsetIndex = 0;

	if (firstInsertionPointFound) {
		offsetIndex = 1;

		++highestAllowedPositionToInsertPerJoblist[OPERATION_LIST_NUMBER - 2];
	}

	operationsGroups.insert(operationsGroups.begin() + HIGHEST_POSSIBLE_POSITION + offsetIndex, group);

	firstInsertionPointFound = true;
}

void OptimizerGrouping::after_grouping()
{
	Debug::function_start(__FUNCTION__);

	const int POSITION_SECOND_LAST_GROUP = operationsGroups.size() - 2;

	for (int indexCurrentGroup = POSITION_SECOND_LAST_GROUP; indexCurrentGroup >= 0; --indexCurrentGroup) {
		OperationsGroup currentGroup = operationsGroups[indexCurrentGroup];

		if (has_group_with_same_toolnumber_below(indexCurrentGroup)) {
			for (int indexCurrentOperation = currentGroup.get_operations().size() - 1; indexCurrentOperation >= 0; --indexCurrentOperation) {
				try_to_move_operation_to_group_below(indexCurrentGroup, indexCurrentOperation);
			}
		}

		try_to_move_group_below(indexCurrentGroup);
	}

	Debug::function_exit(__FUNCTION__);
}

bool OptimizerGrouping::has_group_with_same_toolnumber_below(const int &indexgroup) const
{
	const int TOOLNUMBER_SOURCE_GROUP = operationsGroups[indexgroup].get_toolnumber();

	for (int i = indexgroup + 1; i <= operationsGroups.size() - 1; ++i) {
		if (operationsGroups[i].get_toolnumber() == TOOLNUMBER_SOURCE_GROUP) {
			return true;
		}
	}

	return false;
}

bool OptimizerGrouping::dependencies_between_old_and_new_position_for_joboperation(const int &indexoldgroup, const int &indexoperation, const int &indexnewgroup) const
{
	Debug::function_start(__FUNCTION__);

	//printf("INDEX OLD GROUP: %d INDEX OPERATION: %d, INDEX NEW GROUP: %d\n", indexoldgroup, indexoperation, indexnewgroup);

	JobOperation operation = operationsGroups[indexoldgroup].get_operations()[indexoperation];

	// Checking own group
	if (indexoperation < operationsGroups[indexoldgroup].get_operations().size() - 1) {
		for (int j = indexoperation + 1; j <= operationsGroups[indexoldgroup].get_operations().size() - 1; ++j) {
			printf("CHECKING OWN GROUP %d OPERATION %d\n", indexoldgroup, j);

			if (operationsGroups[indexoldgroup].get_operations()[j] > operation) {
				printf("DEPENDENCY FOUND, NOT MOVING\n");
				return true;
			}
		}
	}

	// Checking next groups
	for (int i = indexoldgroup + 1; i < indexnewgroup; ++i) {
		for (int j = 0; j <= operationsGroups[i].get_operations().size() - 1; ++j) {
			printf("CHECKING GROUP %d, OPERATION: %d\n", i, j);
			if (operationsGroups[i].get_operations()[j] > operation) {
				printf("DEPENDENCY FOUND, NOT MOVING\n");
				return true;
			}
		}
	}

	Debug::function_exit(__FUNCTION__);

	return false;
}

void OptimizerGrouping::try_to_move_operation_to_group_below(const int &indexgroup, const int &indexoperation)
{
	Debug::function_start(__FUNCTION__);
	printf("GROUP: %d OPERATION: %d\n", indexgroup, indexoperation);

	JobOperation operation = operationsGroups[indexgroup].get_operations()[indexoperation];
	const int POSITION_LAST_GROUP = operationsGroups.size() - 1;

	for (int indexCurrentGroup = POSITION_LAST_GROUP; indexCurrentGroup > indexgroup; --indexCurrentGroup) {
		printf("MOVE TO GROUP %d?\n", indexCurrentGroup);

		if (operationsGroups[indexCurrentGroup].get_toolnumber() == operation.toolNumber) {
			printf("GROUP %d HAS MATCHING TOOLNUMBER\n", indexCurrentGroup);

			if (!dependencies_between_old_and_new_position_for_joboperation(indexgroup, indexoperation, indexCurrentGroup)) {

				move_operation_to_group(indexgroup, indexoperation, indexCurrentGroup);

				break;
			}
		}
	}

	Debug::function_exit(__FUNCTION__);
}

void OptimizerGrouping::try_to_move_group_below(const int &indexgroup)
{
	Debug::function_start(__FUNCTION__);

	int lowestPositionPossible = operationsGroups.size() - 1;

	for (int indexOperation = operationsGroups[indexgroup].get_operations().size() - 1; indexOperation >= 0; --indexOperation) {
		for (int indexGroup = indexgroup + 1; indexGroup <= operationsGroups.size() - 1; ++indexGroup) {
			for (int indexOperationGroupBelow = 0; indexOperationGroupBelow <= operationsGroups[indexGroup].get_operations().size() - 1; ++indexOperationGroupBelow) {
				if (operationsGroups[indexGroup].get_operations()[indexOperationGroupBelow] > operationsGroups[indexgroup].get_operations()[indexOperation]) {
					lowestPositionPossible = std::min(lowestPositionPossible, indexGroup - 1);
				}
				if (lowestPositionPossible == indexgroup) { break; }
			}
			if (lowestPositionPossible == indexgroup) { break; }
		}
		if (lowestPositionPossible == indexgroup) { break; }
	}

	// TODO: New function
	if (lowestPositionPossible > indexgroup) {
		OperationsGroup group = operationsGroups[indexgroup];

		operationsGroups.erase(operationsGroups.begin() + indexgroup);
		operationsGroups.insert(operationsGroups.begin() + lowestPositionPossible, group);
	}

	Debug::function_exit(__FUNCTION__);
}

void OptimizerGrouping::move_operation_to_group(const int &indexoldgroup, const int &indexoperation, const int &indexnewgroup)
{
	Debug::function_start(__FUNCTION__);
	printf("DELETE FROM GROUP %d OPERATION %d, ADD TO GROUP %d\n", indexoldgroup, indexoperation, indexnewgroup);

	JobOperation operationToMove = operationsGroups[indexoldgroup].get_operations()[indexoperation];

	operationsGroups[indexnewgroup].add_operation_at_start(operationToMove);

	operationsGroups[indexoldgroup].erase_operation(indexoperation);

	delete_group_if_empty(indexoldgroup);

	Debug::function_exit(__FUNCTION__);
}

void OptimizerGrouping::delete_group_if_empty(const int &indexgroup)
{
	Debug::function_start(__FUNCTION__);

	if (operationsGroups[indexgroup].get_operations().size() == 0) {
		printf("DELETE GROUP %d\n", indexgroup);

		operationsGroups.erase(operationsGroups.begin() + indexgroup);
	}

	Debug::function_exit(__FUNCTION__);
}