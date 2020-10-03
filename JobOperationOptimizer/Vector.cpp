#include "Vector.h"

Vector::Vector()
{
	x = 0.0;
	y = 0.0;
	z = 0.0;
}

Vector::Vector(const double &x, const double &y, const double &z) :
	x(x), y(y), z(z)
{ }

double Vector::calculate_distance_to_vector(const Vector &vector) const
{
	const double LENGTH_X = x - vector.x;
	const double LENGTH_Y = y - vector.y;
	const double LENGTH_Z = z - vector.z;

	const double LENGTH_TOTAL = sqrt(pow(LENGTH_X, 2) + pow(LENGTH_Y, 2) + pow(LENGTH_Z, 2));

	return LENGTH_TOTAL;
}

bool Vector::operator==(const Vector &vector) const
{
	if (abs(this->x - vector.x) < MAX_DELTA_FOR_EQUALITY
		&& abs(this->y - vector.y) < MAX_DELTA_FOR_EQUALITY
		&& abs(this->z - vector.z) < MAX_DELTA_FOR_EQUALITY) {
		return true;
	}

	return false;
}

void Vector::operator=(const Vector &vector)
{
	this->x = vector.x;
	this->y = vector.y;
	this->z = vector.z;
}