#pragma once

#include <string>


constexpr float PI = 3.14159265358979323846f;
constexpr float MIN_PI = 3.14f;
constexpr float HALF_PI = 1.57079632679489661923f;
constexpr float QUARTER_PI = 0.7853982f;

/**
* function to map a value from one range proportionally to another. 
*
* @param valueToMap: the incoming value to be converted
* @param startOne: lower bound of the value's current range
* @param endOne: upper bound of the value's current range
* @param startTwo: lower bound of the value's target range
* @param endTwo: upper bound of the value's target range
*
* Returns the proportional number in the new range.
*/
template<class type>
type mapper(type valueToMap, type startOne, type endOne, type startTwo, type endTwo){
	return (1 - ((valueToMap - startOne) / (endOne - startOne))) * startTwo + ((valueToMap - startOne) / (endOne - startOne)) * endTwo;
}

/**
* function to limit an incoming value between a maximum and minimum value. If the value to be constrained is larger or smaller than
* the max or min, return either the max or min depending on which limit was exceeded. Otherwise simply return the number sent.
*
* @param numToConstrain: the incoming value to be constrained.
* @param min: lower bound.
* @param max: upper bound.
* 
* Returns: constrained number
*/
template<class type>
type constrain(type numToConstrain, type min, type max){
	return (numToConstrain <= min) ? min : (numToConstrain >= max) ? max : numToConstrain;
}

template <class type>
type toRadians(type degrees){
    return (degrees * PI) / 180;
}

template <class type>
type toDegrees(type radians){
    return (radians * 180) / PI;
}
