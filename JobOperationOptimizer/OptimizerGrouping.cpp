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
	for (int i = 0; i <= jobLists.size() - 1; ++i) {
		firstInsertionPointFound = false;

		if (i == 0) {
			init_groups(jobLists[i]);

			continue;
		}

		add_joblist_to_list(jobLists[i]);
	}

	after_grouping(operationsGroups);
	currentBestSolution = operationsGroups;

	after_optimizing();

	for (const auto &group : currentBestSolution) {
		group.print_group();
	}
}


void OptimizerGrouping::print_groups() const
{
	for (const auto &group : operationsGroups) {
		group.print_group();
	}
}

void OptimizerGrouping::init_groups(const JobList &joblist)
{
	for (int indexJob = 0; indexJob <= joblist.get_amount_of_jobs() - 1; ++indexJob) {
		for (int indexOperation = 0; indexOperation <= joblist.get_jobs()[indexJob].get_amount_of_operations() - 1; ++indexOperation) {
			if ((indexJob == 0 && indexOperation == 0) 
				|| joblist.get_jobs()[indexJob].get_operations()[indexOperation].toolNumber != operationsGroups[operationsGroups.size() - 1].get_toolnumber()) {

				add_new_group_at_end(joblist.get_jobs()[indexJob].get_operations()[indexOperation]);
			}
			else {
				operationsGroups[operationsGroups.size() - 1].add_operation(joblist.get_jobs()[indexJob].get_operations()[indexOperation]);
			}
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
	else if (HIGHEST_POSSIBLE_POSITION > 0 && (HIGHEST_POSSIBLE_POSITION + 1) < operationsGroups.size()
		&& operationsGroups[HIGHEST_POSSIBLE_POSITION + 1].get_toolnumber() == OPERATION_TOOL_NUMBER) {
		operationsGroups[HIGHEST_POSSIBLE_POSITION + 1].add_operation(operation);
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

void OptimizerGrouping::add_new_group_at_end(const JobOperation &operation)
{
	OperationsGroup group(operation.toolNumber);
	group.add_operation(operation);

	operationsGroups.push_back(group);
}


void OptimizerGrouping::after_grouping(std::vector<OperationsGroup> &groups, const bool &trytomovegroupbelow)
{
	for (int indexCurrentGroup = groups.size() - 2; indexCurrentGroup >= 0; --indexCurrentGroup) {
		OperationsGroup currentGroup = groups[indexCurrentGroup];

		if (has_group_with_same_toolnumber_below(groups, indexCurrentGroup)) {
			for (int indexCurrentOperation = currentGroup.get_operations().size() - 1; indexCurrentOperation >= 0; --indexCurrentOperation) {
				try_to_move_operation_to_group_below(groups, indexCurrentGroup, indexCurrentOperation);
			}
		}

		if (trytomovegroupbelow) {
			try_to_move_group_below(groups, indexCurrentGroup);
		}
	}
}

void OptimizerGrouping::after_optimizing()
{
	for (int indexGroup = operationsGroups.size() - 2; indexGroup >= 0; --indexGroup) {
		OperationsGroup currentGroup = operationsGroups[indexGroup];

		if (currentGroup.get_operations().size() >= 2) {
			for (int indexOperation = currentGroup.get_operations().size() - 1; indexOperation >= 0; --indexOperation) {
				const int LOWEST_POSITION_POSSIBLE = find_lowest_position_possible(operationsGroups, indexGroup, indexOperation);

				if (LOWEST_POSITION_POSSIBLE > indexGroup + 1) {
					std::vector<OperationsGroup> operationsGroupsAlternativeSolution = operationsGroups;

					JobOperation operationToMove = operationsGroupsAlternativeSolution[indexGroup].get_operations()[indexOperation];
					OperationsGroup newGroup(operationToMove.toolNumber);
					newGroup.add_operation(operationToMove);

					operationsGroupsAlternativeSolution.insert(operationsGroupsAlternativeSolution.begin() + LOWEST_POSITION_POSSIBLE, newGroup);
					operationsGroupsAlternativeSolution[indexGroup].erase_operation(indexOperation);

					after_grouping(operationsGroupsAlternativeSolution, false);

					if (operationsGroupsAlternativeSolution.size() < currentBestSolution.size()) {
						currentBestSolution = operationsGroupsAlternativeSolution;
					}
				}
			}
		}
	}
}


bool OptimizerGrouping::has_group_with_same_toolnumber_below(std::vector<OperationsGroup> &groups, const int &indexgroup) const
{
	const int TOOLNUMBER_SOURCE_GROUP = groups[indexgroup].get_toolnumber();

	for (int i = indexgroup + 1; i <= groups.size() - 1; ++i) {
		if (groups[i].get_toolnumber() == TOOLNUMBER_SOURCE_GROUP) {
			return true;
		}
	}

	return false;
}

bool OptimizerGrouping::has_dependencies_between_old_and_new_position_for_joboperation(std::vector<OperationsGroup> &groups, const int &indexoldgroup, const int &indexoperation, const int &indexnewgroup) const
{
	JobOperation operation = groups[indexoldgroup].get_operations()[indexoperation];

	// Checking own group
	if (indexoperation < groups[indexoldgroup].get_operations().size() - 1) {
		for (int j = indexoperation + 1; j <= groups[indexoldgroup].get_operations().size() - 1; ++j) {
			if (groups[indexoldgroup].get_operations()[j] > operation) {
				return true;
			}
		}
	}

	// Checking next groups
	for (int i = indexoldgroup + 1; i < indexnewgroup; ++i) {
		for (int j = 0; j <= groups[i].get_operations().size() - 1; ++j) {
			if (groups[i].get_operations()[j] > operation) {
				return true;
			}
		}
	}

	return false;
}

void OptimizerGrouping::try_to_move_operation_to_group_below(std::vector<OperationsGroup> &groups, const int &indexgroup, const int &indexoperation)
{
	JobOperation operation = groups[indexgroup].get_operations()[indexoperation];

	for (int indexCurrentGroup = groups.size() - 1; indexCurrentGroup > indexgroup; --indexCurrentGroup) {
		if (groups[indexCurrentGroup].get_toolnumber() == operation.toolNumber) {
			if (!has_dependencies_between_old_and_new_position_for_joboperation(groups, indexgroup, indexoperation, indexCurrentGroup)) {
				move_operation_to_group(groups, indexgroup, indexoperation, indexCurrentGroup);

				break;
			}
		}
	}
}

void OptimizerGrouping::try_to_move_group_below(std::vector<OperationsGroup> &groups, const int &indexgroup)
{
	int lowestPositionPossible = groups.size();

	for (int indexOperation = groups[indexgroup].get_operations().size() - 1; indexOperation >= 0; --indexOperation) {
		lowestPositionPossible = std::min(lowestPositionPossible, find_lowest_position_possible(groups, indexgroup, indexOperation, false));

		if (lowestPositionPossible <= indexgroup + 1) { break; }
	}

	if (lowestPositionPossible > indexgroup + 1) {
		OperationsGroup group = groups[indexgroup];

		groups.insert(groups.begin() + lowestPositionPossible, group);
		groups.erase(groups.begin() + indexgroup);
	}
}

void OptimizerGrouping::move_operation_to_group(std::vector<OperationsGroup> &groups, const int &indexoldgroup, const int &indexoperation, const int &indexnewgroup)
{
	JobOperation operationToMove = groups[indexoldgroup].get_operations()[indexoperation];

	groups[indexnewgroup].add_operation_at_start(operationToMove);

	groups[indexoldgroup].erase_operation(indexoperation);

	delete_group_if_empty(groups, indexoldgroup);
}

void OptimizerGrouping::delete_group_if_empty(std::vector<OperationsGroup> &groups, const int &indexgroup)
{
	if (groups[indexgroup].get_operations().size() == 0) {
		groups.erase(groups.begin() + indexgroup);
	}
}

int OptimizerGrouping::find_lowest_position_possible(std::vector<OperationsGroup> &groups, const int &indexgroup, const int &indexoperation, const bool &checksamegroup) const
{
	JobOperation operation = groups[indexgroup].get_operations()[indexoperation];

	if (checksamegroup) {
		if (indexoperation < groups[indexgroup].get_operations().size() - 1) {
			for (int indexOperation = indexoperation + 1; indexOperation <= groups[indexgroup].get_operations().size() - 1; ++indexOperation) {
				if (groups[indexgroup].get_operations()[indexOperation] > operation) {
					return indexgroup;
				}
			}
		}
	}

	for (int indexGroup = indexgroup + 1; indexGroup <= groups.size() - 1; ++indexGroup) {
		for (int indexOperation = 0; indexOperation <= groups[indexGroup].get_operations().size() - 1; ++indexOperation) {
			if (groups[indexGroup].get_operations()[indexOperation] > operation) {
				return indexGroup;
			}
		}
	}

	return groups.size();
}