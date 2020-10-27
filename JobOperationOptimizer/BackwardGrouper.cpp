#include "BackwardGrouper.h"

BackwardGrouper::BackwardGrouper(const OperationsGroupList &list) :
	groupList(list), POSITION_LIMIT_BOTTOM(INT_MAX)
{ }

BackwardGrouper::BackwardGrouper(const OperationsGroupList & list, const int &positionlimitbottom) :
	groupList(list), POSITION_LIMIT_BOTTOM(positionlimitbottom)
{ }


void BackwardGrouper::group()
{
	for (int indexGroup = groupList.get_amount_of_groups() - 2; indexGroup >= 0; --indexGroup) {
		if (groupList.has_group_with_same_toolnumber_below(indexGroup)) {
			for (int indexOperation = groupList.get_amount_of_operations_for_group(indexGroup) - 1; indexOperation >= 0; --indexOperation) {
				try_to_move_operation_to_group_below(indexGroup, indexOperation);
			}
		}

		try_to_move_group_below(indexGroup);
	}
}


OperationsGroupList BackwardGrouper::get_groups() const
{
	return groupList;
}


void BackwardGrouper::try_to_move_operation_to_group_below(const int &positiongroup, const int &positionoperation)
{
	for (int indexGroup = groupList.get_amount_of_groups() - 1; indexGroup > positiongroup; --indexGroup) {
		if (groupList.get_toolnumber_at_position(indexGroup) == groupList.get_toolnumber_at_position(positiongroup, positionoperation)) {
			if (!groupList.has_dependencies_between_positions_for_operation(positiongroup, positionoperation, indexGroup)) {
				groupList.move_operation(positiongroup, positionoperation, indexGroup);

				break;
			}
		}
	}
}

void BackwardGrouper::try_to_move_group_below(const int &position)
{
	int lowestPositionPossible = groupList.get_amount_of_groups();
	const bool SEARCH_FOR_DEPENDENCY_IN_OWN_GROUP = false;
	
	for (int indexOperation = groupList.get_amount_of_operations_for_group(position) - 1; indexOperation >= 0; --indexOperation) {
		lowestPositionPossible = std::min(lowestPositionPossible, groupList.find_lowest_position_possible(position, indexOperation, SEARCH_FOR_DEPENDENCY_IN_OWN_GROUP));
	
		if (lowestPositionPossible <= position + 1) { break; }
	}
	
	if (lowestPositionPossible > position + 1 && lowestPositionPossible <= POSITION_LIMIT_BOTTOM) {
		groupList.move_group(position, lowestPositionPossible);
	}
}
