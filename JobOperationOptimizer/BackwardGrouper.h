#ifndef BACKWARDGROUPER_H_
#define BACKWARDGROUPER_H_

#include "OperationsGroupList.h"

class BackwardGrouper
{
public:
	BackwardGrouper(const OperationsGroupList &list);
	BackwardGrouper(const OperationsGroupList &list, const int &positionlimitbottom);

	void group();

	OperationsGroupList get_groups() const;
private:
	OperationsGroupList groupList;

	const int POSITION_LIMIT_BOTTOM;

	void try_to_move_operation_to_group_below(const int &positiongroup, const int &positionoperation);
	void try_to_move_group_below(const int &position);
};

#endif