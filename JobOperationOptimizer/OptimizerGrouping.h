#ifndef OPTIMIZERGROUPING_H_
#define OPTIMIZERGROUPING_H_

#include <vector>

#include "OperationsGroup.h"
#include "JobList.h"

#include "Debug.h"

class OptimizerGrouping
{
public:
	void append_ordered_joblist(const JobList &joblist);

	void optimize_toolchanges();

	void print_groups() const;

private:
	std::vector<OperationsGroup> operationsGroups;

	std::vector<JobList> jobLists;

	std::vector<int> highestAllowedPositionToInsertPerJoblist;
	bool firstInsertionPointFound = false;

	void init_groups(const JobList &joblist);
	void add_joblist_to_list(const JobList &joblist);
	void add_operation_to_list(const JobOperation &operation);
	void add_new_group(const JobOperation &operation);

	void after_grouping();

	bool has_group_with_same_toolnumber_below(const int &indexgroup) const;
	bool dependencies_between_old_and_new_position_for_joboperation(const int &indexoldgroup, const int &indexoperation, const int &indexnewgroup) const;
	void try_to_move_operation_to_group_below(const int &indexoldgroup, const int &indexoperation);
	void move_operation_to_group(const int &indexoldgroup, const int &indexoperation, const int &indexnewgroup);
	void delete_group_if_empty(const int &indexgroup);
};

#endif