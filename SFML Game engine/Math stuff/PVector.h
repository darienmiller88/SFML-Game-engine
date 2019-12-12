#pragma once
#include <SFML/Graphics.hpp>

/*
* "PVector" stands for "physics vector", and denotes an object which is meant to represent a quantity that has a magt=nitude and a direction.
* x and y will represent the x and y components of the vector;
*/
class PVector : public sf::Vector2f{
	public:
		PVector(float x, float y);//construct one from a x and y component
		void add(float x, float y);
		void add(const PVector &vector);
		void subtract(float x, float y);
		void mult(float scalar);
		void div(float scalar);
		void set(float x, float y);
		void set(const PVector &vector);
		void setMagnitude(float magnitude);
		void normalize();
		void setAngle(float angle);
		float getX() const;
		float getY() const;
		float getMagnitude() const;
		float getAngle() const;
		std::string toString() const;

		//operators
		PVector &operator += (const PVector &rhs);
		bool operator == (const PVector &rhs);
		bool operator != (const PVector& rhs);
	private:
		float angle, magnitude;
		void calcMagnitude(float newX, float newY);
};

