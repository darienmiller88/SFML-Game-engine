#pragma once
#include <random>


class Random{
	public:
		Random();

		template<class Type>
		Type getIntInRange(Type min, Type max);

		double getDoubleInRange(double min, double max);
		float getFloatInRange(float min, float max);
	private:
		std::random_device seed;
		std::default_random_engine rnGen;
};

template<class Type>
inline Type Random::getIntInRange(Type min, Type max){
	return std::uniform_int_distribution<Type>(min, max - 1)(rnGen);
}
