#include "JobOperation.h"

JobOperation::JobOperation()
{
	name = "";
	listNumber = 0;
	jobNumber = 0;
	operationNumber = 0;
	toolNumber = 0;
}

JobOperation::JobOperation(const std::string name, const short &listnumber, const short &jobnumber, const short &operationnumber, const short &toolnumber, const Vector &startposition, const Vector &endposition) :
	name(name), listNumber(listnumber), jobNumber(jobnumber), operationNumber(operationnumber), toolNumber(toolnumber), startPosition(startposition), endPosition(endposition)
{ }

bool JobOperation::operator==(const JobOperation &operation) const
{
	if (this->name == operation.name
		&& this->listNumber == operation.listNumber
		&& this->jobNumber == operation.jobNumber
		&& this->operationNumber == operation.operationNumber
		&& this->toolNumber == operation.toolNumber
		&& this->startPosition == operation.startPosition
		&& this->endPosition == operation.endPosition) {
		return true;
	}

	return false;
}

bool JobOperation::operator>(const JobOperation &operation) const
{
	if (this->listNumber == operation.listNumber) {
		if (this->jobNumber == operation.jobNumber
			&& this->operationNumber > operation.operationNumber) {
			return true;
		}
		else if (this->jobNumber > operation.jobNumber) {
			return true;
		}
	}

	return false;
}

void JobOperation::operator=(const JobOperation &operation)
{
	this->name = operation.name;
	this->listNumber = operation.listNumber;
	this->jobNumber = operation.jobNumber;
	this->operationNumber = operation.operationNumber;
	this->toolNumber = operation.toolNumber;
	this->startPosition = operation.startPosition;
	this->endPosition = operation.endPosition;
}

void JobOperation::print_operation() const
{
	std::cout << "   Op. " << name << " --> ";
	printf("(L%d ; J%d ; O%d) ->  %d ; %.2f, %.2f, %.2f ;; %.2f, %.2f, %.2f\n",
		listNumber, jobNumber, operationNumber, toolNumber,
		startPosition.x, startPosition.y, startPosition.z,
		endPosition.x, endPosition.y, endPosition.z);
}