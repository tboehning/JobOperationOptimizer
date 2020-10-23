#include "JobOperation.h"

JobOperation::JobOperation()
{
	name = "";
	jobNumber = 0;
	operationNumber = 0;
	toolNumber = 0;
}

JobOperation::JobOperation(const std::string &name, const int &jobnumber, const int &operationnumber, const int &toolnumber, const Vector &startposition, const Vector &endposition) :
	name(name), jobNumber(jobnumber), operationNumber(operationnumber), toolNumber(toolnumber), startPosition(startposition), endPosition(endposition)
{ }

bool JobOperation::operator==(const JobOperation &operation) const
{
	if (this->name == operation.name 
		&& this->jobNumber == operation.jobNumber 
		&& this->operationNumber == operation.operationNumber 
		&& this->toolNumber == operation.toolNumber 
		&& this->startPosition == operation.startPosition 
		&& this->endPosition == operation.endPosition) {
		return true;
	}

	return false;
}

void JobOperation::operator=(const JobOperation &operation)
{
	this->name = operation.name;
	this->jobNumber = operation.jobNumber;
	this->operationNumber = operation.operationNumber;
	this->toolNumber = operation.toolNumber;
	this->startPosition = operation.startPosition;
	this->endPosition = operation.endPosition;
}

void JobOperation::print_operation() const
{
	std::cout << "   Op. " << name << " --> ";
	printf("(%d ; %d) ->  %d ; %.2f, %.2f, %.2f ;; %.2f, %.2f, %.2f\n",
		jobNumber, operationNumber, toolNumber,
		startPosition.x, startPosition.y, startPosition.z,
		endPosition.x, endPosition.y, endPosition.z);
}
