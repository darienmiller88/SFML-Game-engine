#include "FrameRate.h"
#include "..//Asset Manager/AssetManager.h"
#include <string>

FrameRate::FrameRate() : frameCount(0), frameRate(0), delta(0), lastTime(sf::Time::Zero){
	
}

void FrameRate::calculate(){
	sf::Time current = clock.getElapsedTime();
	delta += (current - lastTime).asMilliseconds();
	lastTime = current;
	frameCount++; 

	//std::cout << "delta: " << delta.count() << "\n";
	if (delta > 1000) {
		delta -= 1000;
		frameRate = frameCount;
		frameCount = 0;
	}
}

void FrameRate::draw(sf::RenderWindow &window){
	window.setTitle(std::to_string((double)frameRate));
}

std::ostream & operator<<(std::ostream & os, const FrameRate &f){
	return os << f.frameRate << "\n";
}