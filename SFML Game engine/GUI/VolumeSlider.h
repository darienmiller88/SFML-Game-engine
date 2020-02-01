#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

class VolumeSlider{
	public:

		/*
		* \brief Constructor to create a volume slider using an initial position and size.
		*
		* @param musicFile - File path for the desired music.
		* @param position - The position the volume slider will be placed, relative to the top left corner of course
		* @param size - the size of the volume slider, in terms of pixels regarding width (size.x) and height(size.y)
		* The size is defaulted to 200 pixels wide, and 5 pixels high using a default argument.
		*/
		VolumeSlider(const std::string &musicFile, const sf::Vector2f &position, const sf::Vector2f &size = sf::Vector2f(200.f, 5.f));
		void drawSlider(sf::RenderWindow &window);

		//This function is meant to be called inside of the while(window.pollEvent(e)){} loop. 
		void eventHandler(const sf::RenderWindow &window, sf::Event e);

		//Set a texture to the slider, or null if you want to remove it after setting it. 
		void setSliderTexture(const sf::Texture *texure);
		void setSliderColor(const sf::Color &color);
		void setVolumeColor(const sf::Color &color);
		sf::Music &getMusic();
	private:
		//States for button/events
		bool mouseInsideRect = false;
		bool dragging = false;
		
		//Keep track of the mouse states
		sf::Vector2f mouseRectOffset;
		int mouseX = 0;
		int mouseY = 0;

		//In order to emulate the shape of the volume slider body on most volume sliders, I have to make use of a 
		//rectangular body, and two circular endpoints to simulate that shape.
		sf::CircleShape leftEndPoint, rightEndPoint, slider;
		sf::RectangleShape volumeBody, volumeLevelColoring;
		sf::Color volumeColor, sliderColor;
		sf::Text percentageDisplay;
		sf::Texture sliderTexture;
		sf::Music music;
		float currentVolumeLevel;
};