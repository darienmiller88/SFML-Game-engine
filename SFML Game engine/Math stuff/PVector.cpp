#include "PVector.h"
#include "Math.h"
#include <cmath>

PVector::PVector(float x, float y) {
	this->x = x;
	this->y = y;
	calcMagnitude(x, y);
}

void PVector::add(float x, float y){
	this->x += x;
	this->y += y;
	calcMagnitude(this->x, this->y);
}

void PVector::add(const PVector &vector){
	add(vector.x, vector.y);
}

void PVector::subtract(float x, float y){
	this->x -= x;
	this->y -= y;
}

void PVector::mult(float scalar){
	x *= scalar;
	y *= scalar;
}

void PVector::div(float scalar){
	x /= scalar;
	y /= scalar;
}

void PVector::set(const PVector &vector){
	set(vector.x, vector.y);
}

void PVector::setMagnitude(float magnitude){
	this->magnitude = magnitude;
	x = magnitude * cos(angle);
	y = magnitude * sin(angle);
}

void PVector::normalize(){
	setMagnitude(1);
}

void PVector::setAngle(float angle){
	x = magnitude * cos(angle);
	y = magnitude * sin(angle);
	calcMagnitude(x, y);
}

float PVector::getX() const{
	return x;
}

float PVector::getY() const{
	return y;
}

float PVector::getMagnitude() const{
	return magnitude;
}

float PVector::getAngle() const{
	return angle;
}

 std::string PVector::toString() const{
	return "PVector Object : [" +std::to_string(x) + "," + std::to_string(x) + "]";
}

void PVector::calcMagnitude(float newX, float newY){
	angle = toDegrees(atan(newY / newX));
	magnitude = sqrt(pow(newX, 2) + pow(newY, 2));
}

void PVector::set(float x, float y){
	this->x = x;
	this->y = y;
	calcMagnitude(this->x, this->y);
}

PVector& PVector::operator += (const PVector& rhs) {
	x += rhs.x;
	y += rhs.y;
	calcMagnitude(x, y);

	return *this;
}

bool PVector::operator==(const PVector& rhs) {
	return this->x == rhs.x and this->y == rhs.y;
}

bool PVector::operator!=(const PVector& rhs) {
	return !operator==(rhs);
}