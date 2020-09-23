#include "JobList.h"
#include "Permutation.h"
#include "Misc.h"
#include "DecisionStackList.h"

int main() {
	// Real example
	// Correct Order for toolchanges: 1.1 -> 2.1 -> 3.1 -> 4.1 -> 3.2 -> 4.2
	// Tool Changes: 7 Length 907.25
	Job job1(1, "Tasche Schruppen");
	Job job2(2, "Tasche Schlichten");
	Job job3(3, "Bohren und Gewinde 1");
	Job job4(4, "Bohren und Gewinde 2");

	Misc::fill_first_job(job1);
	Misc::fill_second_job(job2);
	Misc::fill_third_job(job3);
	Misc::fill_fourth_job(job4);

	job2.append_dependency(job1);
	job3.append_dependency(job2);
	job4.append_dependency(job2);

	// Can be left out or added. Transitive dependencies are recursively calculated
	//job3.append_dependency(job1); 
	//job4.append_dependency(job1);

	{
		// Second example for optimal results length: 0.0, changes: 4
	/*Job job1(1, "TEST");
	Job job2(2, "TEST");
	Job job3(3, "TEST");

	Misc::fill_first_job_length_zero(job1);
	Misc::fill_second_job_length_zero(job2);
	Misc::fill_third_job_length_zero(job3);*/
	}
 	
	//JobList allJobs;
	//allJobs.append_job(job1);
	//allJobs.append_job(job2);
	//allJobs.append_job(job3);
	//allJobs.append_job(job4);

	////allJobs.print_jobs();

	//Permutation p(allJobs);

	//p.print_permutation();

	DecisionStack s1(job1);
	DecisionStack s2(job2);
	DecisionStack s3(job3);
	DecisionStack s4(job3);

	//s4.print_decisions();

	DecisionStackList list;
	list.append_decision_stack(job1);
	list.append_decision_stack(job2);
	list.append_decision_stack(job3);
	list.append_decision_stack(job4);

	//list.print_decision_stacks();

	list.make_decision(job1.get_operations()[0]);

	/*std::vector<JobOperation> decisionSet = list.calculate_current_decision_set();

	for (const auto &decision : decisionSet) {
		decision.print_operation();
	}*/

	//list.print_decision_stacks();

	list.make_decision(job2.get_operations()[0]);

	//list.print_decision_stacks();

	//std::vector<JobOperation> decisionSet = list.calculate_current_decision_set();

	/*for (const auto &decision : decisionSet) {
		decision.print_operation();
	}*/

	list.make_decision(job3.get_operations()[0]);

	//std::vector<JobOperation> decisionSet = list.calculate_current_decision_set();

	/*for (const auto &decision : decisionSet) {
		decision.print_operation();
	}*/

	list.make_decision(job3.get_operations()[1]);

	//std::vector<JobOperation> decisionSet = list.calculate_current_decision_set();

	/*for (const auto &decision : decisionSet) {
		decision.print_operation();
	}*/

	list.make_decision(job3.get_operations()[2]);

	std::vector<JobOperation> decisionSet = list.calculate_current_decision_set();

	for (const auto &decision : decisionSet) {
		decision.print_operation();
	}


	//list.print_decision_stacks();

	return 0;
}
