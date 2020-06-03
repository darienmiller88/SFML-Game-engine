#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>

class FrameRate{
	public:
		//@param position: position of the text object containing the FPS that will be drawn onto the screen.
		FrameRate(const sf::Vector2f &position);
		void calculate();
		void draw(sf::RenderWindow &window);
		float getDeltaTime() const;
		friend std::ostream &operator <<(std::ostream &os, const FrameRate &f);
	private:
		sf::Clock clock;
		sf::Time lastTime;
		sf::Int32 delta;
		sf::Text fpsText;
		int frameRate, frameCount;
		float timeBetweenFrames;
};

