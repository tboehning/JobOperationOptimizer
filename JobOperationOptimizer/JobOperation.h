#ifndef JOBOPERATION_H_
#define JOBOPERATION_H_

#include <string>
#include <iostream>

#include "Vector.h"

class JobOperation
{
public:
	std::string name;
	short listNumber;
	short jobNumber;
	short operationNumber;
	short toolNumber;
	Vector startPosition;
	Vector endPosition;

	JobOperation();
	JobOperation(const std::string &name, const short &listnumber, const short &jobnumber, const short &operationnumber, const short &toolnumber,
		const Vector &startposition, const Vector &endposition);

	bool operator==(const JobOperation &operation) const;
	bool operator>(const JobOperation &operation) const;
	void operator=(const JobOperation &operation);

	void print_operation() const;
};

#endif