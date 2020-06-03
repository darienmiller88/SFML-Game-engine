#include "Random.h"

Random::Random() : rnGen(seed()){
}

double Random::getDoubleInRange(double min, double max){
	return std::uniform_real_distribution<double>(min, max)(rnGen);
}

float Random::getFloatInRange(float min, float max){
	return std::uniform_real_distribution<float>(min, max)(rnGen);
}

