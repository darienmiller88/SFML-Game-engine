#include "FrameRate.h"
#include "..//Asset Manager/AssetManager.h"
#include <string>

FrameRate::FrameRate(const sf::Vector2f &position) : frameCount(0), frameRate(0), delta(0), timeBetweenFrames(0),
lastTime(sf::Time::Zero), fpsText("FPS: 0", AssetManager::get().getDefaultFont(Fonts::ARIAL_ITALIC))
{
	fpsText.setPosition(position);
	fpsText.setCharacterSize(20);
}

void FrameRate::calculate(){
	sf::Time current = clock.getElapsedTime();
	timeBetweenFrames = (current - lastTime).asSeconds();
	delta += (current - lastTime).asMilliseconds();
	lastTime = current;
	frameCount++; 

	fpsText.setString("FPS: " + std::to_string(frameRate));
	if (delta > 1000) {
		delta -= 1000;
		frameRate = frameCount;
		frameCount = 0;
	}
}

void FrameRate::draw(sf::RenderWindow &window){
	window.draw(fpsText);
}

float FrameRate::getDeltaTime() const{
	return timeBetweenFrames;
}

std::ostream &operator<<(std::ostream &os, const FrameRate &f){
	return os << f.frameRate << "\n";
}