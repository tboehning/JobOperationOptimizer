#include "OperationsGroup.h"

OperationsGroup::OperationsGroup(const int &toolnumber) :
    toolNumber(toolnumber)
{
}

void OperationsGroup::add_operation(const JobOperation &operation)
{
    operations.push_back(operation);
}

void OperationsGroup::add_operation_at_start(const JobOperation &operation)
{
    operations.insert(operations.begin(), operation);
}

void OperationsGroup::erase_operation(const int &position)
{
    operations.erase(operations.begin() + position);
}

std::vector<JobOperation> OperationsGroup::get_operations() const
{
    return operations;
}

int OperationsGroup::get_toolnumber() const
{
    return toolNumber;
}

long long OperationsGroup::get_amount_of_operations() const
{
    return operations.size();
}

void OperationsGroup::print_group() const
{
    printf("*** OPERATIONS GROUP ***\n");

    for (const auto &operation : operations) {
        operation.print_operation();
    }
}

void OperationsGroup::operator=(const OperationsGroup &group)
{
    this->toolNumber = group.toolNumber;
    this->operations = group.operations;
}