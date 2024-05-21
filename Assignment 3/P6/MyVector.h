#pragma once 

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

namespace P6 {
	class MyVector 
	{
		public:
			float x, y, z;

			MyVector() : x(0),y(0),z(0) {}
			MyVector(const float _x, const float _y, const float _z);

			explicit operator glm::vec3() const;
			

			float Magnitude();
			MyVector Direction();
			void operator+=(const MyVector v); // addition
			void operator-=(const MyVector v); // subtraction
			MyVector scalarMultiplication(float ScaleValue);
			void operator*=(const MyVector v); // Component Product
			float dotProduct(const MyVector v);
			MyVector vectorProduct(const MyVector v);

			
			
	};
}