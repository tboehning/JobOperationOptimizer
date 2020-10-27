#include "OperationsGroupList.h"

void OperationsGroupList::add_group_at_position(const OperationsGroup &group, const int &position)
{
	groups.insert(groups.begin() + position, group);
}

void OperationsGroupList::create_group_with_operation_at_end(const JobOperation &operation)
{
	OperationsGroup group(operation.toolNumber);
	group.add_operation(operation);

	groups.push_back(group);
}

void OperationsGroupList::create_group_with_operation_at_position(const JobOperation &operation, const int &position)
{
	OperationsGroup group(operation.toolNumber);
	group.add_operation(operation);

	groups.insert(groups.begin() + position, group);
}


void OperationsGroupList::add_operation_to_position_at_start(const JobOperation &operation, const int &position)
{
	groups[position].add_operation_at_start(operation);
}

void OperationsGroupList::add_operation_to_position_at_end(const JobOperation &operation, const int &position)
{
	groups[position].add_operation(operation);
}

void OperationsGroupList::add_operation_to_last_group(const JobOperation &operation)
{
	groups.back().add_operation(operation);
}


void OperationsGroupList::move_group(const int &positionold, const int &positionnew)
{
	OperationsGroup group = groups[positionold];

	groups.insert(groups.begin() + positionnew, group);
	groups.erase(groups.begin() + positionold);

}

void OperationsGroupList::move_operation(const int &positionoldgroup, const int &oldpositionoperation, const int &positionnewgroup)
{
	JobOperation operationToMove = get_operation_at_position(positionoldgroup, oldpositionoperation);

	add_operation_to_position_at_start(operationToMove, positionnewgroup);

	groups[positionoldgroup].erase_operation(oldpositionoperation);

	if (get_amount_of_operations_for_group(positionoldgroup) == 0) {
		groups.erase(groups.begin() + positionoldgroup);
	}
}

void OperationsGroupList::move_operation_and_create_new_group(const int &positionoldgroup, const int &oldpositionoperation, const int &positionnewgroup)
{
	JobOperation operationToMove = get_operation_at_position(positionoldgroup, oldpositionoperation);

	OperationsGroup newGroup(operationToMove.toolNumber);
	newGroup.add_operation(operationToMove);

	groups.insert(groups.begin() + positionnewgroup, newGroup);
	groups[positionoldgroup].erase_operation(oldpositionoperation);
}


JobOperation OperationsGroupList::get_operation_at_position(const int &positiongroup, const int &positionoperation) const
{
	return groups[positiongroup].get_operations()[positionoperation];
}


int OperationsGroupList::get_toolnumber_at_position(const int &position) const
{
	return groups[position].get_toolnumber();
}

int OperationsGroupList::get_toolnumber_at_position(const int &positiongroup, const int &positionoperation) const
{
	return groups[positiongroup].get_operations()[positionoperation].toolNumber;
}

int OperationsGroupList::get_toolnumber_of_last_group() const
{
	return groups.back().get_toolnumber();
}


long long OperationsGroupList::get_amount_of_operations_for_group(const int &position) const
{
	return groups[position].get_amount_of_operations();
}

long long OperationsGroupList::get_amount_of_groups() const
{
	return groups.size();
}


bool OperationsGroupList::has_group_with_same_toolnumber_below(const int &position) const
{
	const int TOOLNUMBER_SOURCE_GROUP = get_toolnumber_at_position(position);

	for (int i = position + 1; i <= get_amount_of_groups() - 1; ++i) {
		if (get_toolnumber_at_position(i) == TOOLNUMBER_SOURCE_GROUP) {
			return true;
		}
	}

	return false;
}

bool OperationsGroupList::has_dependencies_between_positions_for_operation(const int &positionoldgroup, const int &oldpositionoperation, const int &positionnewgroup) const
{
	JobOperation operation = get_operation_at_position(positionoldgroup, oldpositionoperation);

	// Checking own group
	if (oldpositionoperation < get_amount_of_operations_for_group(positionoldgroup) - 1) {
		for (int indexOperation = oldpositionoperation + 1; indexOperation <= get_amount_of_operations_for_group(positionoldgroup) - 1; ++indexOperation) {
			if (get_operation_at_position(positionoldgroup, indexOperation) > operation) {
				return true;
			}
		}
	}

	// Checking next groups
	for (int indexGroup = positionoldgroup + 1; indexGroup < positionnewgroup; ++indexGroup) {
		for (int indexOperation = 0; indexOperation <= get_amount_of_operations_for_group(indexGroup) - 1; ++indexOperation) {
			if (get_operation_at_position(indexGroup, indexOperation) > operation) {
				return true;
			}
		}
	}

	return false;
}


int OperationsGroupList::find_lowest_position_possible(const int &positiongroup, const int &positionoperation, const bool &checksamegroup) const
{
	JobOperation operation = get_operation_at_position(positiongroup, positionoperation);

	if (checksamegroup) {
		if (positionoperation < get_amount_of_operations_for_group(positiongroup) - 1) {
			for (int indexOperation = positionoperation + 1; indexOperation <= get_amount_of_operations_for_group(positiongroup) - 1; ++indexOperation) {
				if (get_operation_at_position(positiongroup, indexOperation) > operation) {
					return positiongroup;
				}
			}
		}
	}

	for (int indexGroup = positiongroup + 1; indexGroup <= groups.size() - 1; ++indexGroup) {
		for (int indexOperation = 0; indexOperation <= get_amount_of_operations_for_group(indexGroup) - 1; ++indexOperation) {
			if (get_operation_at_position(indexGroup, indexOperation) > operation) {
				return indexGroup;
			}
		}
	}

	return groups.size();
}


void OperationsGroupList::print_groups() const
{
	for (const auto &group : groups) {
		group.print_group();
	}
}
