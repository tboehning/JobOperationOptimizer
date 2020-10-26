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
	std::vector<OperationsGroup> currentBestSolution;
	std::vector<OperationsGroup> operationsGroups;

	std::vector<JobList> jobLists;

	std::vector<int> highestAllowedPositionToInsertPerJoblist;
	bool firstInsertionPointFound = false;

	void init_groups(const JobList &joblist);
	void add_joblist_to_list(const JobList &joblist);
	void add_operation_to_list(const JobOperation &operation);
	void add_new_group_at_next_position_for_joblist(const JobOperation &operation);
	void add_new_group_at_end(const JobOperation &operation);

	void after_grouping(std::vector<OperationsGroup> &groups, const bool &trytomovegroupbelow = true);
	void after_optimizing();

	bool has_group_with_same_toolnumber_below(std::vector<OperationsGroup> &groups, const int &indexgroup) const;
	bool has_dependencies_between_old_and_new_position_for_joboperation(std::vector<OperationsGroup> &groups, const int &indexoldgroup, const int &indexoperation, const int &indexnewgroup) const;
	void try_to_move_operation_to_group_below(std::vector<OperationsGroup> &groups, const int &indexoldgroup, const int &indexoperation);
	void try_to_move_group_below(std::vector<OperationsGroup> &groups, const int &indexgroup);
	void move_operation_to_group(std::vector<OperationsGroup> &groups, const int &indexoldgroup, const int &indexoperation, const int &indexnewgroup);
	void delete_group_if_empty(std::vector<OperationsGroup> &groups, const int &indexgroup);
	int find_lowest_position_possible(std::vector<OperationsGroup> &groups, const int &indexgroup, const int &indexoperation, const bool &checksamegroup = true) const;
};

#endif