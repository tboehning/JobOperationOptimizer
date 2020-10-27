#ifndef OPTIMIZERGROUPING_H_
#define OPTIMIZERGROUPING_H_

#include <vector>

#include "OperationsGroupList.h"
#include "JobList.h"
#include "BackwardGrouper.h"

class OptimizerGrouping
{
public:
	void append_joblist(const JobList &joblist);

	void optimize_toolchanges();

	void print_groups() const;

private:
	std::vector<JobList> jobLists;

	OperationsGroupList groupList;
	OperationsGroupList currentBestSolution;
	
	std::vector<int> highestAllowedPositionToInsertPerJoblist;
	bool firstInsertionPointFound = false;

	void init_groups(const JobList &joblist);
	void add_joblist_to_groups(const JobList &joblist);
	void add_operation_to_groups(const JobOperation &operation);
	void add_new_group_at_next_position_for_joblist(const JobOperation &operation);

	void after_grouping(OperationsGroupList &groups, const int &lowestlimitgroup);
	void after_grouping(OperationsGroupList &groups);
	void after_optimizing();
};

#endif