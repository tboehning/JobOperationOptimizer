#include "Misc.h"
#include "OptimizerRecursive.h"
#include "OptimizerGreedy.h"
#include <chrono>

int main() {
	// Joblist1
	Job job11(1, "Tasche Schruppen 1");
	Job job12(2, "Tasche Schlichten 2");
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

	// JobList 3
	Job job31(1, "Tasche Schruppen 1");
	Job job32(2, "Tasche Schlichten 2");
	Job job33(3, "Bohren und Gewinde 1");
	Job job34(4, "Bohren und Gewinde 2");

	Misc::fill_joblist3_job1(job31);
	Misc::fill_joblist3_job2(job32);
	Misc::fill_joblist3_job3(job33);
	Misc::fill_joblist3_job4(job34);

	JobList list3;
	list3.append_job(job31);
	list3.append_job(job32);
	list3.append_job(job33);
	list3.append_job(job34);


	// Second example for optimal results length: 0.0, changes: 4	
	/*Job job1(1, "Job 1");
	Job job2(2, "Job 2");
	Job job3(3, "Job 3");

	Misc::fill_first_job_length_zero(job1);
	Misc::fill_second_job_length_zero(job2);
	Misc::fill_third_job_length_zero(job3);*/

	OptimizerRecursive optimizer;
	//OptimizerGreedy optimizer;
	optimizer.append_ordered_joblist(list1);
	optimizer.append_ordered_joblist(list2);
	optimizer.append_ordered_joblist(list3);
	//optimizer.append_joblist_with_dependencies(list1);
	//optimizer.append_joblist_with_dependencies(list2);

	optimizer.print_decision_stacks();
	std::cout << "\n";


	auto start = std::chrono::high_resolution_clock::now();

	optimizer.optimize_toolchanges();
	//optimizer.optimize_transitionlength();

	auto finish = std::chrono::high_resolution_clock::now();
	std::chrono::duration<double> elapsed = finish - start;
	std::cout << "Elapsed time: " << elapsed.count() << " s\n";

	return 0;
}
