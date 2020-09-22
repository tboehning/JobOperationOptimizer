#include "JobOperation.h"

JobOperation::JobOperation() :
	jobNumber(0), operationNumber(0), toolNumber(0), startPosition(Vector(0.0, 0.0, 0.0)), endPosition(Vector(0.0, 0.0, 0.0))
{ }

JobOperation::JobOperation(const int &jobnumber, const int &operationnumber, const int &toolnumber, const Vector &startposition, const Vector &endposition) :
	jobNumber(jobnumber), operationNumber(operationnumber), toolNumber(toolnumber), startPosition(startposition), endPosition(endposition)
{ }

void JobOperation::operator=(const JobOperation &task)
{
	this->jobNumber = task.jobNumber;
	this->operationNumber = task.operationNumber;
	this->toolNumber = task.toolNumber;
	this->startPosition = task.startPosition;
	this->endPosition = task.endPosition;
}

bool JobOperation::operator<(const JobOperation &task) const
{
	if (jobNumber == task.jobNumber) {
		return operationNumber < task.operationNumber;
	}
	else {
		return jobNumber < task.jobNumber;
	}
}