#include "PermutationPointer.h"

PermutationPointer::PermutationPointer(const int &size)
{
	index = 0;

	operations.reserve(size);
}

void PermutationPointer::append_operation(const JobOperation &operation)
{
	JobOperation *pointer = &operation;
}
