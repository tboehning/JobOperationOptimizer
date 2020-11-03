#include "JobList.h"

namespace Misc {
	const double OFFSET_X = 100.0;

	void fill_joblist1_job1(Job &job) {
		const int JOB_NUMBER = job.number;

		job.append_operation(JobOperation("Schruppen L1 J1", 1, JOB_NUMBER, 1, 1, Vector(0.0, 0.0, 0.0), Vector(10.3, 12.0, 5.64)));
	}

	void fill_joblist1_job2(Job &job) {
		const int JOB_NUMBER = job.number;

		job.append_operation(JobOperation("Schlichten L1 J2", 1, JOB_NUMBER, 1, 2, Vector(100.3, 0.0, 0.0), Vector(42.12, 126.53, 641.5)));
	}

	void fill_joblist1_job3(Job &job) {
		const int JOB_NUMBER = job.number;

		job.append_operation(JobOperation("Bohren L1 J3", 1, JOB_NUMBER, 1, 3, Vector(54.1, 1.64, 12.54), Vector(65.1, 0.0, 421.0)));
		job.append_operation(JobOperation("Senken L1 J3", 1, JOB_NUMBER, 2, 4, Vector(54.1, 1.64, 12.54), Vector(52.2, 567.1, 65.1)));
		//job.append_operation(JobOperation("Gewindebohren L1 J3", 1, JOB_NUMBER, 3, 5, Vector(54.1, 1.64, 12.54), Vector(12.67, 75.1, 89.1)));
	}

	void fill_joblist1_job4(Job &job) {
		const int JOB_NUMBER = job.number;

		job.append_operation(JobOperation("Bohren L1 J4", 1, JOB_NUMBER, 1, 3, Vector(321.2, 789.1, 437.1), Vector(853.123, 123.1, 588.9)));
		job.append_operation(JobOperation("Senken L1 J4", 1, JOB_NUMBER, 2, 4, Vector(321.2, 789.1, 437.1), Vector(534.12, 122.0, 566.64)));
		job.append_operation(JobOperation("Gewindebohren L1 J4", 1, JOB_NUMBER, 3, 5, Vector(321.2, 789.1, 437.1), Vector(104.13, 172.0, 51.64)));
	}

	// Start joblist 2 

	void fill_joblist2_job1(Job &job) {
		const int JOB_NUMBER = job.number;

		job.append_operation(JobOperation("Schruppen L2 J1", 2, JOB_NUMBER, 1, 1, Vector(0.0 + OFFSET_X, 0.0, 0.0), Vector(10.3 + OFFSET_X, 12.0, 5.64)));
	}

	void fill_joblist2_job2(Job &job) {
		const int JOB_NUMBER = job.number;

		//job.append_operation(JobOperation("Schlichten L2 J2", 2, JOB_NUMBER, 1, 2, Vector(100.3 + OFFSET_X, 0.0, 0.0), Vector(42.12 + OFFSET_X, 126.53, 641.5)));
	}

	void fill_joblist2_job3(Job &job) {
		const int JOB_NUMBER = job.number;

		job.append_operation(JobOperation("Bohren L2 J3", 2, JOB_NUMBER, 1, 3, Vector(54.1 + OFFSET_X, 1.64, 12.54), Vector(65.1 + OFFSET_X, 0.0, 421.0)));
		job.append_operation(JobOperation("Senken L2 J3", 2, JOB_NUMBER, 2, 4, Vector(54.1 + OFFSET_X, 1.64, 12.54), Vector(52.2 + OFFSET_X, 567.1, 65.1)));
		job.append_operation(JobOperation("Gewindebohren L2 J3", 2, JOB_NUMBER, 3, 5, Vector(54.1 + OFFSET_X, 1.64, 12.54), Vector(12.67 + OFFSET_X, 75.1, 89.1)));
	}

	void fill_joblist2_job4(Job &job) {
		const int JOB_NUMBER = job.number;

		job.append_operation(JobOperation("Bohren L2 J4", 2, JOB_NUMBER, 1, 3, Vector(321.2 + OFFSET_X, 789.1, 437.1), Vector(853.123 + OFFSET_X, 123.1, 588.9)));
		job.append_operation(JobOperation("Senken L2 J4", 2, JOB_NUMBER, 2, 4, Vector(321.2 + OFFSET_X, 789.1, 437.1), Vector(534.12 + OFFSET_X, 122.0, 566.64)));
		job.append_operation(JobOperation("Gewindebohren L2 J4", 2, JOB_NUMBER, 3, 5, Vector(321.2 + OFFSET_X, 789.1, 437.1), Vector(104.13 + OFFSET_X, 172.0, 51.64)));
	}

	void fill_joblist3_job1(Job &job) {
		const int JOB_NUMBER = job.number;

		job.append_operation(JobOperation("Schruppen L3 J1", 3, JOB_NUMBER, 1, 1, Vector(0.0 + OFFSET_X * 2, 0.0, 0.0), Vector(10.3 + OFFSET_X * 2, 12.0, 5.64)));
	}

	void fill_joblist3_job2(Job &job) {
		const int JOB_NUMBER = job.number;

		job.append_operation(JobOperation("Schlichten L3 J2", 3, JOB_NUMBER, 1, 2, Vector(100.3 + OFFSET_X * 2, 0.0, 0.0), Vector(42.12 + OFFSET_X * 2, 126.53, 641.5)));
	}

	void fill_joblist3_job3(Job &job) {
		const int JOB_NUMBER = job.number;

		////job.append_operation(JobOperation("Bohren L3 J3", 3, JOB_NUMBER, 1, 3, Vector(54.1 + OFFSET_X * 2, 1.64, 12.54), Vector(65.1 + OFFSET_X * 2, 0.0, 421.0)));
		////job.append_operation(JobOperation("Senken L3 J3", 3, JOB_NUMBER, 2, 4, Vector(54.1 + OFFSET_X * 2, 1.64, 12.54), Vector(52.2 + OFFSET_X * 2, 567.1, 65.1)));
		////job.append_operation(JobOperation("Gewindebohren L3 J3", 3, JOB_NUMBER, 3, 5, Vector(54.1 + OFFSET_X * 2, 1.64, 12.54), Vector(12.67 + OFFSET_X * 2, 75.1, 89.1)));
	}

	void fill_joblist3_job4(Job &job) {
		const int JOB_NUMBER = job.number;

		////job.append_operation(JobOperation("Bohren L3 J4", 3, JOB_NUMBER, 1, 3, Vector(321.2 + OFFSET_X * 2, 789.1, 437.1), Vector(853.123 + OFFSET_X * 2, 123.1, 588.9)));
		////job.append_operation(JobOperation("Senken L3 J4", 3, JOB_NUMBER, 2, 4, Vector(321.2 + OFFSET_X * 2, 789.1, 437.1), Vector(534.12 + OFFSET_X * 2, 122.0, 566.64)));
		////job.append_operation(JobOperation("Gewindebohren L3 J4", 3, JOB_NUMBER, 3, 5, Vector(321.2 + OFFSET_X * 2, 789.1, 437.1), Vector(104.13 + OFFSET_X * 2, 172.0, 51.64)));
	}

	//////////////////////////////////// NEW EXAMPLE

	void l1j1(Job &job) {
		const int JOB_NUMBER = job.number;

		job.append_operation(JobOperation("Schruppen L1 J1", 1, JOB_NUMBER, 1, 1, Vector(0.0, 0.0, 0.0), Vector(10.3, 12.0, 5.64)));
	}

	void l1j2(Job &job) {
		const int JOB_NUMBER = job.number;

		job.append_operation(JobOperation("Bohren L1 J2", 1, JOB_NUMBER, 1, 2, Vector(100.3, 0.0, 0.0), Vector(42.12, 126.53, 641.5)));
	}

	void l1j3(Job &job) {
		const int JOB_NUMBER = job.number;

		job.append_operation(JobOperation("Senken L1 J3", 1, JOB_NUMBER, 1, 3, Vector(54.1, 1.64, 12.54), Vector(65.1, 0.0, 421.0)));
		job.append_operation(JobOperation("Bohren L1 J3", 1, JOB_NUMBER, 2, 2, Vector(54.1, 1.64, 12.54), Vector(52.2, 567.1, 65.1)));
		job.append_operation(JobOperation("Senken L1 J3", 1, JOB_NUMBER, 3, 3, Vector(54.1, 1.64, 12.54), Vector(65.1, 0.0, 421.0)));

	}

	void l1j4(Job &job) {
		const int JOB_NUMBER = job.number;

		//job.append_operation(JobOperation("Schruppen L1 J4", 1, JOB_NUMBER, 1, 3, Vector(321.2, 789.1, 437.1), Vector(853.123, 123.1, 588.9)));
	}

	// Start joblist 2 

	void l2j1(Job &job) {
		const int JOB_NUMBER = job.number;

		//job.append_operation(JobOperation("Schruppen L2 J1", 2, JOB_NUMBER, 1, 1, Vector(0.0 + OFFSET_X, 0.0, 0.0), Vector(10.3 + OFFSET_X, 12.0, 5.64)));
	}

	void l2j2(Job &job) {
		const int JOB_NUMBER = job.number;

		job.append_operation(JobOperation("Bohren L2 J2", 2, JOB_NUMBER, 1, 2, Vector(100.3 + OFFSET_X, 0.0, 0.0), Vector(42.12 + OFFSET_X, 126.53, 641.5)));
	}

	void l2j3(Job &job) {
		const int JOB_NUMBER = job.number;

		job.append_operation(JobOperation("Senken L2 J3", 2, JOB_NUMBER, 1, 3, Vector(54.1 + OFFSET_X, 1.64, 12.54), Vector(52.2 + OFFSET_X, 567.1, 65.1)));
		job.append_operation(JobOperation("Bohren L2 J3", 2, JOB_NUMBER, 2, 2, Vector(54.1 + OFFSET_X, 1.64, 12.54), Vector(12.67 + OFFSET_X, 75.1, 89.1)));
		job.append_operation(JobOperation("Senken L2 J3", 2, JOB_NUMBER, 3, 3, Vector(54.1 + OFFSET_X, 1.64, 12.54), Vector(12.67 + OFFSET_X, 75.1, 89.1)));
		job.append_operation(JobOperation("Schruppen L2 J3", 2, JOB_NUMBER, 4, 1, Vector(54.1 + OFFSET_X, 1.64, 12.54), Vector(12.67 + OFFSET_X, 75.1, 89.1)));
	}

	void l2j4(Job &job) {
		const int JOB_NUMBER = job.number;

		//job.append_operation(JobOperation("Bohren L2 J4", 2, JOB_NUMBER, 1, 3, Vector(321.2 + OFFSET_X, 789.1, 437.1), Vector(853.123 + OFFSET_X, 123.1, 588.9)));
		//job.append_operation(JobOperation("Senken L2 J4", 2, JOB_NUMBER, 2, 4, Vector(321.2 + OFFSET_X, 789.1, 437.1), Vector(534.12 + OFFSET_X, 122.0, 566.64)));
		//job.append_operation(JobOperation("Gewindebohren L2 J4", 2, JOB_NUMBER, 3, 5, Vector(321.2 + OFFSET_X, 789.1, 437.1), Vector(104.13 + OFFSET_X, 172.0, 51.64)));
	}
}

/*void fill_first_job_length_zero(Job &job) {
		const int JOB_NUMBER = job.number;
		job.append_operation(JobOperation("11", JOB_NUMBER, 1, 1, Vector(0.0, 0.0, 0.0), Vector(10.3, 12.0, 5.64)));
		job.append_operation(JobOperation("12", JOB_NUMBER, 2, 2, Vector(42.2, 52.123, 68.0), Vector(30.12, 10.1, 200.3)));
		job.append_operation(JobOperation("13", JOB_NUMBER, 3, 3, Vector(100.0, 200.0, 300.0), Vector(20.11, 54.12, 0.0)));
		job.append_operation(JobOperation("14", JOB_NUMBER, 4, 4, Vector(15.3, 12.0, 5.64), Vector(0.21, 532.1, 345.14)));
	}
	void fill_second_job_length_zero(Job &job) {
		const int JOB_NUMBER = job.number;
		job.append_operation(JobOperation("21", JOB_NUMBER, 1, 1, Vector(10.3, 12.0, 5.64), Vector(15.8, 65.1, 14.21)));
		job.append_operation(JobOperation("22", JOB_NUMBER, 2, 2, Vector(30.12, 10.1, 200.3), Vector(20.3, 43.0, 10.64)));
		job.append_operation(JobOperation("23", JOB_NUMBER, 3, 3, Vector(20.11, 54.12, 0.0), Vector(11.3, 112.0, 45.64)));
		job.append_operation(JobOperation("24", JOB_NUMBER, 4, 4, Vector(0.21, 532.1, 345.14), Vector(43.3, 1.0, 2112.64)));
	}
	void fill_third_job_length_zero(Job &job) {
		const int JOB_NUMBER = job.number;
		job.append_operation(JobOperation("31", JOB_NUMBER, 1, 1, Vector(15.8, 65.1, 14.21), Vector(42.2, 52.123, 68.0)));
		job.append_operation(JobOperation("32", JOB_NUMBER, 2, 2, Vector(20.3, 43.0, 10.64), Vector(100.0, 200.0, 300.0)));
		job.append_operation(JobOperation("33", JOB_NUMBER, 3, 3, Vector(11.3, 112.0, 45.64), Vector(15.3, 12.0, 5.64)));
		job.append_operation(JobOperation("34",JOB_NUMBER, 4, 4, Vector(43.3, 1.0, 2112.64), Vector(41.3, 87.2, 1000.4)));
	}*/