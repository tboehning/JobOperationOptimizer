#include "JobList.h"
#include "Permutation.h"
#include "Misc.h"
#include "DecisionStackList.h"
#include "Optimizer.h"

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

	// *************************************************************

	Optimizer optimizer;
	optimizer.append_job(job1);
	optimizer.append_job(job2);
	optimizer.append_job(job3);
	optimizer.append_job(job4);

	optimizer.optimize_toolchanges();
	optimizer.optimize_transition_length();

	{
		// Second example for optimal results length: 0.0, changes: 4
	/*Job job1(1, "TEST");
	Job job2(2, "TEST");
	Job job3(3, "TEST");

	Misc::fill_first_job_length_zero(job1);
	Misc::fill_second_job_length_zero(job2);
	Misc::fill_third_job_length_zero(job3);*/
	}

	return 0;
}
