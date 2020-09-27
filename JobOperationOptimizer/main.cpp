#include "JobList.h"
#include "Permutation.h"
#include "Misc.h"
#include "DecisionStackList.h"
#include "Optimizer.h"
#include <chrono>

int main() {
	// Real example
	// Correct Order for toolchanges: 1.1 -> 2.1 -> 3.1 -> 4.1 -> 3.2 -> 4.2
	// Tool Changes: 7 Length 907.25
	Job job11(1, "Tasche Schruppen");
	Job job12(2, "Tasche Schlichten");
	Job job13(3, "Bohren und Gewinde 1");
	Job job14(4, "Bohren und Gewinde 2");

	Misc::fill_joblist1_job1(job11);
	Misc::fill_joblist1_job2(job12);
	Misc::fill_joblist1_job3(job13);
	Misc::fill_joblist1_job4(job14);

	job12.append_dependency(job11);
	job13.append_dependency(job12);
	job14.append_dependency(job12);

	JobList list1;
	list1.append_job(job11);
	list1.append_job(job12);
	list1.append_job(job13);
	list1.append_job(job14);

	// Joblist 2
	Job job21(1, "Tasche Schruppen 2");
	Job job22(2, "Tasche Schlichten 2");
	Job job23(3, "Bohren und Gewinde 1 2");
	Job job24(4, "Bohren und Gewinde 2 2");

	Misc::fill_joblist2_job1(job21);
	Misc::fill_joblist2_job2(job22);
	Misc::fill_joblist2_job3(job23);
	Misc::fill_joblist2_job4(job24);

	job22.append_dependency(job21);
	job23.append_dependency(job22);
	job24.append_dependency(job22);

	JobList list2;
	list2.append_job(job21);
	list2.append_job(job22);
	list2.append_job(job23);
	list2.append_job(job24);

	// *************************************************************

	// Second example for optimal results length: 0.0, changes: 4	
	//Job job11(1, "TEST");
	//Job job12(2, "TEST");
	//Job job13(3, "TEST");

	//Misc::fill_first_job_length_zero(job11);
	//Misc::fill_second_job_length_zero(job12);
	//Misc::fill_third_job_length_zero(job13);

	////job12.append_dependency(job11);

	Optimizer optimizer;
	optimizer.append_joblist(list1);
	optimizer.append_joblist(list2);

	//optimizer.append_job(job11);
	//optimizer.append_job(job12);
	//optimizer.append_job(job13);
	//optimizer.append_job(job14);

	auto start = std::chrono::high_resolution_clock::now();

	optimizer.optimize_toolchanges();
	//optimizer.optimize_transition_length();

	auto finish = std::chrono::high_resolution_clock::now();
	std::chrono::duration<double> elapsed = finish - start;
	std::cout << "Elapsed time: " << elapsed.count() << " s\n";

	return 0;
}
