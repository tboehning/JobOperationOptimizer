#include "JobList.h"
#include "Permutation.h"

void fill_first_job(Job &job) {
	job.append_operation(JobOperation(1, 1, 1, Vector(0.0, 0.0, 0.0), Vector(10.3, 12.0, 5.64)));
	job.append_operation(JobOperation(1, 2, 1, Vector(20.1, 100.3, 50.0), Vector(30.12, 10.1, 200.3)));
	job.append_operation(JobOperation(1, 3, 3, Vector(30.12, 100.3, 0.0), Vector(10.3, 12.0, 5.64)));
}

void fill_second_job(Job &job) {
	job.append_operation(JobOperation(2, 1, 2, Vector(100.3, 0.0, 0.0), Vector(10.3, 12.0, 5.64)));
	job.append_operation(JobOperation(2, 2, 3, Vector(400.0, 500.0, 600.0), Vector(20.3, 43.0, 10.64)));
	job.append_operation(JobOperation(2, 3, 1, Vector(10.3, 12.0, 5.0), Vector(10.3, 12.0, 5.64)));
}

void fill_third_job(Job &job) {
	job.append_operation(JobOperation(3, 1, 1, Vector(0.0, 0.0, 0.0), Vector(10.3, 12.0, 5.64)));
	job.append_operation(JobOperation(3, 2, 3, Vector(30.12, 10.1, 200.3), Vector(10.3, 12.0, 5.64)));
	job.append_operation(JobOperation(3, 3, 1, Vector(32.1, 40.2, 0.0), Vector(15.3, 12.0, 5.64)));
	//job.append_operation(JobOperation(3, 4, 2, Vector(12.0, 312.2, 0.0), Vector(41.3, 87.2, 1000.4))); // Optional
	//job.append_operation(JobOperation(3, 5, 2, Vector(12.0, 312.2, 0.0), Vector(41.3, 87.2, 1000.4))); // Optional
}

void fill_first_job_length_zero(Job &job) {
	job.append_operation(JobOperation(1, 1, 1, Vector(0.0, 0.0, 0.0), Vector(10.3, 12.0, 5.64)));
	job.append_operation(JobOperation(1, 2, 1, Vector(42.2, 52.123, 68.0), Vector(30.12, 10.1, 200.3)));
	job.append_operation(JobOperation(1, 3, 3, Vector(100.0, 200.0, 300.0), Vector(20.11, 54.12, 0.0)));
}

void fill_second_job_length_zero(Job &job) {
	job.append_operation(JobOperation(2, 1, 2, Vector(10.3, 12.0, 5.64), Vector(15.8, 65.1, 14.21)));
	job.append_operation(JobOperation(2, 2, 3, Vector(30.12, 10.1, 200.3), Vector(20.3, 43.0, 10.64)));
	job.append_operation(JobOperation(2, 3, 1, Vector(20.11, 54.12, 0.0), Vector(11.3, 112.0, 45.64)));
	// job.append_operation(JobOperation(2, 4, 1, Vector(312.31, 315.1, 54.1), Vector(43.3, 1.0, 2112.64))); // Optional
}

void fill_third_job_length_zero(Job &job) {
	job.append_operation(JobOperation(3, 1, 1, Vector(15.8, 65.1, 14.21), Vector(42.2, 52.123, 68.0)));
	job.append_operation(JobOperation(3, 2, 3, Vector(20.3, 43.0, 10.64), Vector(100.0, 200.0, 300.0)));
	job.append_operation(JobOperation(3, 3, 1, Vector(11.3, 112.0, 45.64), Vector(15.3, 12.0, 5.64)));
	// job.append_operation(JobOperation(3, 4, 2, Vector(12.0, 312.2, 0.0), Vector(41.3, 87.2, 1000.4))); // Optional
	// job.append_operation(JobOperation(3, 5, 2, Vector(12.0, 312.2, 0.0), Vector(41.3, 87.2, 1000.4))); // Optional
}

int main() {
	Job job1;
	Job job2;
	Job job3;

	fill_first_job(job1);
	fill_second_job(job2);
	fill_third_job(job3);

	JobList joblist;
	joblist.append_job(job1);
	joblist.append_job(job2);
	joblist.append_job(job3);

	joblist.print_information();

	Permutation p(joblist);

	p.print_permutation();

	return 0;
}
