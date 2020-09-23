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

	double calculate_distance_to_vector(const Vector &secondvector) const;
	bool operator==(const Vector &vector) const;
	void operator=(const Vector &vector);
	Vector operator-(const Vector &vector) const;
private:
	const double MAX_DELTA = 0.01;
};

#endif