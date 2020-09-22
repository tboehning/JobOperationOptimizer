#ifndef JOBOPERATION_H_
#define JOBOPERATION_H_

#include "Vector.h"

class JobOperation
{
public:
	int jobNumber;
	int operationNumber;
	int toolNumber;
	Vector startPosition;
	Vector endPosition;

	JobOperation();
	JobOperation(const int &jobnumber, const int &operationnumber, const int &toolnumber, const Vector &startposition, const Vector &endposition);
	void operator=(const JobOperation &task);
	bool operator<(const JobOperation &task) const;
};

#endif