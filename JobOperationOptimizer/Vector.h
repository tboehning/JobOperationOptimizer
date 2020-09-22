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
	Vector operator-(const Vector &vector) const;
};

#endif