#ifndef VECTOR_H_
#define VECTOR_H_

#include <cmath>

class Vector
{
public:
	double x;
	double y;
	double z;

	Vector();
	Vector(const double &x, const double &y, const double &z);

	double calculate_distance_to_vector(const Vector &vector) const;
	bool operator==(const Vector &vector) const;
	void operator=(const Vector &vector);

private:
	const double MAX_DELTA_FOR_EQUALITY = 0.01;
};

#endif