#include "JobList.h"

namespace Misc {
	void fill_first_job(Job &job) {
		const int JOB_NUMBER = job.number;

		job.append_operation(JobOperation("Schruppen", JOB_NUMBER, 1, 1, Vector(0.0, 0.0, 0.0), Vector(10.3, 12.0, 5.64)));
	}

	void fill_second_job(Job &job) {
		const int JOB_NUMBER = job.number;

		job.append_operation(JobOperation("Schlichten", JOB_NUMBER, 1, 2, Vector(100.3, 0.0, 0.0), Vector(42.12, 126.53, 641.5)));
	}

	void fill_third_job(Job &job) {
		const int JOB_NUMBER = job.number;

		job.append_operation(JobOperation("Bohren", JOB_NUMBER, 1, 3, Vector(54.1, 1.64, 12.54), Vector(65.1, 0.0, 421.0)));
		job.append_operation(JobOperation("Senken", JOB_NUMBER, 2, 4, Vector(54.1, 1.64, 12.54), Vector(52.2, 567.1, 65.1)));
		job.append_operation(JobOperation("Gewindebohren", JOB_NUMBER, 2, 5, Vector(54.1, 1.64, 12.54), Vector(12.67, 75.1, 89.1)));
	}

	void fill_fourth_job(Job &job) {
		const int JOB_NUMBER = job.number;

		job.append_operation(JobOperation("Bohren", JOB_NUMBER, 1, 3, Vector(321.2, 789.1, 437.1), Vector(853.123, 123.1, 588.9)));
		job.append_operation(JobOperation("Senken", JOB_NUMBER, 2, 4, Vector(321.2, 789.1, 437.1), Vector(534.12, 122.0, 566.64)));
		job.append_operation(JobOperation("Gewindebohren", JOB_NUMBER, 2, 6, Vector(321.2, 789.1, 437.1), Vector(104.13, 172.0, 51.64)));
	}

	void fill_first_job_length_zero(Job &job) {
		const int JOB_NUMBER = job.number;

		job.append_operation(JobOperation("TEST", JOB_NUMBER, 1, 1, Vector(0.0, 0.0, 0.0), Vector(10.3, 12.0, 5.64)));
		job.append_operation(JobOperation("TEST", JOB_NUMBER, 2, 2, Vector(42.2, 52.123, 68.0), Vector(30.12, 10.1, 200.3)));
		job.append_operation(JobOperation("TEST", JOB_NUMBER, 3, 3, Vector(100.0, 200.0, 300.0), Vector(20.11, 54.12, 0.0)));
		job.append_operation(JobOperation("TEST", JOB_NUMBER, 4, 4, Vector(321.3, 142.1, 400.0), Vector(0.21, 532.1, 345.14)));
	}

	void fill_second_job_length_zero(Job &job) {
		const int JOB_NUMBER = job.number;

		job.append_operation(JobOperation("TEST", JOB_NUMBER, 1, 1, Vector(10.3, 12.0, 5.64), Vector(15.8, 65.1, 14.21)));
		job.append_operation(JobOperation("TEST", JOB_NUMBER, 2, 2, Vector(30.12, 10.1, 200.3), Vector(20.3, 43.0, 10.64)));
		job.append_operation(JobOperation("TEST", JOB_NUMBER, 3, 3, Vector(20.11, 54.12, 0.0), Vector(11.3, 112.0, 45.64)));
		job.append_operation(JobOperation("TEST", JOB_NUMBER, 4, 4, Vector(0.21, 532.1, 345.14), Vector(43.3, 1.0, 2112.64)));
	}

	void fill_third_job_length_zero(Job &job) {
		const int JOB_NUMBER = job.number;

		job.append_operation(JobOperation("TEST", JOB_NUMBER, 1, 1, Vector(15.8, 65.1, 14.21), Vector(42.2, 52.123, 68.0)));
		job.append_operation(JobOperation("TEST", JOB_NUMBER, 2, 2, Vector(20.3, 43.0, 10.64), Vector(100.0, 200.0, 300.0)));
		job.append_operation(JobOperation("TEST", JOB_NUMBER, 3, 3, Vector(11.3, 112.0, 45.64), Vector(15.3, 12.0, 5.64)));
		job.append_operation(JobOperation("TEST",JOB_NUMBER, 4, 4, Vector(43.3, 1.0, 2112.64), Vector(41.3, 87.2, 1000.4)));
	}
}