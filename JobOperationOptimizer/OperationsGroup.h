#ifndef OPERATIONSGROUP_H_
#define OPERATIONSGROUP_H_

#include <vector>

#include "JobOperation.h"

class OperationsGroup
{
public:
	OperationsGroup(const int &toolnumber);

	void add_operation(const JobOperation &operation);
	void add_operation_at_start(const JobOperation &operation);
	void erase_operation(const int &position);

	std::vector<JobOperation> get_operations() const;
	int get_toolnumber() const;

	long long get_amount_of_operations() const;

	void print_group() const;

	void operator=(const OperationsGroup &group);

private:
	std::vector<JobOperation> operations;

	int toolNumber;
};

#endif