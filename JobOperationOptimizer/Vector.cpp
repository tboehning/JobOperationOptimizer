#include "Vector.h"

Vector::Vector() :
	x(0.0), y(0.0), z(0.0)
{ }

Vector::Vector(const double &x, const double &y, const double &z) :
	x(x), y(y), z(z)
{ }

double Vector::calculate_distance_to_vector(const Vector &secondvector) const
{
	const double LENGTH_X = x - secondvector.x;
	const double LENGTH_Y = y - secondvector.y;
	const double LENGTH_Z = z - secondvector.z;

	const double LENGTH_TOTAL = sqrt(pow(LENGTH_X, 2) + pow(LENGTH_Y, 2) + pow(LENGTH_Z, 2));

	return LENGTH_TOTAL;
}

Vector Vector::operator-(const Vector &vector) const
{
	const double DELTA_X = this->x - vector.x;
	const double DELTA_Y = this->y - vector.y;
	const double DELTA_Z = this->z - vector.z;

	return Vector(DELTA_X, DELTA_Y, DELTA_Z);
}