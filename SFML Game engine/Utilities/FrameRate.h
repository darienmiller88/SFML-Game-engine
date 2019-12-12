#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>

class FrameRate{
	public:
		FrameRate();
		void calculate();
		void draw(sf::RenderWindow &window);
		friend std::ostream &operator <<(std::ostream &os, const FrameRate &f);
	private:
		sf::Clock clock;
		sf::Time lastTime;
		sf::Int32 delta;
		sf::Text fpsText;
		int frameRate, frameCount;
};

