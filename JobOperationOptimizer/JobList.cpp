#include "JobList.h"

JobList::JobList()
{ }

void JobList::append_job(const Job &job)
{
	jobs.push_back(job);
}

int JobList::calculate_tool_changes() const
{
	unsigned int numberOfToolChanges = 0;

	for (const auto &job : jobs) {
		numberOfToolChanges += job.calculate_tool_changes();
	}

	numberOfToolChanges += calculate_tool_changes_between_jobs();

	return numberOfToolChanges;
}

double JobList::calculate_toolpath_from_transitions() const
{
	double lengthToolPath = 0.0;

	for (const auto &job : jobs) {
		lengthToolPath += job.calculate_toolpath_from_transitions();
	}

	lengthToolPath += calculate_toolpath_from_transitions_between_jobs();

	return lengthToolPath;
}

void JobList::print_information() const
{
	const int NUMBER_OF_TOOL_CHANGES = calculate_tool_changes();
	const double LENGTH_TOOLPATH_TRANSITIONS = calculate_toolpath_from_transitions();

	printf("*** JobList Information ***\n");
	printf("Number of tool changes: %d\n", NUMBER_OF_TOOL_CHANGES);
	printf("Length toolpath transitions: %.2f\n", LENGTH_TOOLPATH_TRANSITIONS);

	printf("\n");
}

int JobList::calculate_tool_changes_between_jobs() const
{
	int numberOfToolChangesBetweenJobs = 0;

	for (int i = 1; i < jobs.size(); i++) {
		const int INDEX_PREVIOUS_JOB = i - 1;

		const int TOOL_NUMBER_LAST_OPERATION_PREVIOUS_JOB = jobs[INDEX_PREVIOUS_JOB].operations.back().toolNumber;
		const int TOOL_NUMBER_FIRST_OPERATION_CURRENT_JOB = jobs[i].operations.front().toolNumber;

		if (TOOL_NUMBER_LAST_OPERATION_PREVIOUS_JOB == TOOL_NUMBER_FIRST_OPERATION_CURRENT_JOB) {
			numberOfToolChangesBetweenJobs += 1;
		}
	}

	return numberOfToolChangesBetweenJobs;
}

double JobList::calculate_toolpath_from_transitions_between_jobs() const
{
	int lengthToolPathBetweenJobs = 0.0;

	for (int i = 1; i < jobs.size(); i++) {
		const int INDEX_PREVIOUS_JOB = i - 1;

		const Vector END_POSITION_LAST_OPERATION_PREVIOUS_JOB = jobs[INDEX_PREVIOUS_JOB].operations.back().endPosition;
		const Vector START_POSITION_FIRST_OPERATION_CURRENT_JOB = jobs[i].operations.front().startPosition;

		lengthToolPathBetweenJobs +=
			END_POSITION_LAST_OPERATION_PREVIOUS_JOB.calculate_distance_to_vector(START_POSITION_FIRST_OPERATION_CURRENT_JOB);
	}

	return lengthToolPathBetweenJobs;
}