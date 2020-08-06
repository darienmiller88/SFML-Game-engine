#pragma once
#include <random>


class Random{
	public:
		Random() : rnGen(seed()) {

		}

		template<class Type>
		Type getNumberInRange(Type min, Type max) {
			return std::uniform_int_distribution<Type>(min, max)(rnGen);
		}
	private:
		std::random_device seed;
		std::default_random_engine rnGen;
};