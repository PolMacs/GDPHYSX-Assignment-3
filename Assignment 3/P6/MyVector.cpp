#include "MyVector.h"
#include <cmath>

using namespace P6;

MyVector::MyVector() : x(0), y(0), z(0)
{
}

MyVector::MyVector(const float _x, const float _y, const float _z) : x(_x), y(_y), z(_z) 
{
}

MyVector::operator glm::vec3() const
{
	return glm::vec3(x, y, z);	
}

float MyVector::Magnitude()
{
	return std::sqrt((x * x) + (y * y) + (z * z));
}

MyVector MyVector::Direction()
{
	float magnitude = Magnitude();

	return MyVector(x / magnitude, y / magnitude, z / magnitude);
}

void MyVector::operator+=(const MyVector v)
{
	this->x += v.x;
	this->y += v.y;
	this->z += v.z;
}

void MyVector::operator-=(const MyVector v)
{
	this->x -= v.x;
	this->y -= v.y;
	this->z -= v.z;
}

MyVector MyVector::scalarMultiplication(float ScaleValue)
{
	return MyVector(ScaleValue * x, ScaleValue * y, ScaleValue * z);
}

void MyVector::operator*=(const MyVector v)
{
	this->x *= v.x;
	this->y *= v.y;
	this->z *= v.z;
}

float MyVector::dotProduct(const MyVector v) 
{
	return (this->x * v.x) + (this->y * v.y) + (this->z * v.z);
}

MyVector MyVector::vectorProduct(const MyVector v) 
{
	return MyVector(
		this->y * v.z - this->z * v.y,
		this->z * v.x - this->x * v.z,
		this->x * v.y - this->y * v.x);
}

