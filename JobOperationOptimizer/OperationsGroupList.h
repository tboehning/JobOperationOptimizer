#ifndef OPERATIONSGROUPLIST_H_
#define OPERATIONSGROUPLIST_H_

#include "OperationsGroup.h"

class OperationsGroupList
{
public:
	void add_group_at_position(const OperationsGroup &group, const int &position);
	void create_group_with_operation_at_end(const JobOperation &operation);
	void create_group_with_operation_at_position(const JobOperation &operation, const int &position);

	void add_operation_to_position_at_start(const JobOperation &operation, const int &position);
	void add_operation_to_position_at_end(const JobOperation &operation, const int &position);
	void add_operation_to_last_group(const JobOperation &operation);

	void move_group(const int &positionold, const int &positionnew);
	void move_operation(const int &positionoldgroup, const int &oldpositionoperation, const int &positionnewgroup);
	void move_operation_and_create_new_group(const int &positionoldgroup, const int &oldpositionoperation, const int &positionnewgroup);

	JobOperation get_operation_at_position(const int &positiongroup, const int &positionoperation) const;

	int get_toolnumber_at_position(const int &position) const;
	int get_toolnumber_at_position(const int &positiongroup, const int &positionoperation) const;
	int get_toolnumber_of_last_group() const;

	long long get_amount_of_operations_for_group(const int &position) const;
	long long get_amount_of_groups() const;

	bool has_group_with_same_toolnumber_below(const int &position) const;
	bool has_dependencies_between_positions_for_operation(const int &positionoldgroup, const int &oldpositionoperation, const int &positionnewgroup) const;

	int find_lowest_position_possible(const int &positiongroup, const int &positionoperation, const bool &checksamegroup = true) const;

	void print_groups() const;
private:
	std::vector<OperationsGroup> groups;
};

#endif