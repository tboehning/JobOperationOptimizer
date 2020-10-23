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

	//OptimizerRecursive optimizer;
	OptimizerGreedy optimizer;
	optimizer.append_joblist(list1);
	optimizer.append_joblist(list2);
	//optimizer.append_joblist(list3);

	auto start = std::chrono::high_resolution_clock::now();

	optimizer.optimize_toolchanges();

	auto finish = std::chrono::high_resolution_clock::now();
	std::chrono::duration<double> elapsed = finish - start;
	std::cout << "Elapsed time: " << elapsed.count() << " s\n";

	return 0;
}
