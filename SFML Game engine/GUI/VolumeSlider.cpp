#include "VolumeSlider.h"
#include "SFML Game Engine/Asset Manager/AssetManager.cpp"
#include "SFML Game Engine/Math stuff/Math.h"

VolumeSlider::VolumeSlider(const std::string &musicFile, const sf::Vector2f &position, const sf::Vector2f &size) :
volumeBody({ size.x - size.y, size.y }), leftEndPoint(size.y / 2.f), rightEndPoint(size.y / 2.f), slider(size.y * 2.5f),
percentageDisplay("100%", AssetManager::get().getDefaultFont(Fonts::ARIAL_ITALIC), 20)
{	
	if (!music.openFromFile(musicFile)){
		std::cout << "Could not open file: " << musicFile << "\n";
		exit(1);
	}

	music.play();
	slider.setOrigin(getHalfSize(slider));
	volumeColor = sf::Color(0, 100, 250);

	leftEndPoint.setPosition(position);
	volumeBody.setPosition(getCenterPosition(leftEndPoint).x, position.y);
	rightEndPoint.setPosition(getRightEdge(volumeBody) - getHalfSize(rightEndPoint).x, position.y);
	slider.setPosition(getCenterPosition(rightEndPoint));
	volumeLevelColoring.setPosition(volumeBody.getPosition()); 
	volumeLevelColoring.setSize(volumeBody.getSize());

	volumeLevelColoring.setFillColor(volumeColor);
	leftEndPoint.setFillColor(volumeColor);
}

void VolumeSlider::drawSlider(sf::RenderWindow &window){
	if (dragging == true) {
		slider.setPosition(mouseX - mouseRectOffset.x, slider.getPosition().y);
		float min =  volumeBody.getPosition().x;
		float max = getCenterPosition(rightEndPoint).x;

		//Constrain the x position between the left side of the slider and the right side.
		slider.setPosition(constrain(slider.getPosition().x, min, max), slider.getPosition().y);

		//map the position of the slider to a number between 0 and 100;
		currentVolumeLevel = mapper(slider.getPosition().x, min, max, 0.f, 100.f);

		//Finally, convert the percentage to an integer, and then to a string to be displayed to the screen.
		percentageDisplay.setString(std::to_string(static_cast<int>(currentVolumeLevel)));

		//Set the music volume to the current volume level after it was mapped
		music.setVolume(currentVolumeLevel);

		//Here, we will adjust the length of the volume coloring based on where the slider is.
		volumeLevelColoring.setSize({slider.getPosition().x  - volumeBody.getPosition().x, volumeBody.getSize().y});
	}

	window.draw(leftEndPoint);
	window.draw(rightEndPoint);
	window.draw(volumeBody);
	window.draw(volumeLevelColoring);
	window.draw(slider);
	window.draw(percentageDisplay);
}

void VolumeSlider::eventHandler(const sf::RenderWindow &window, sf::Event e){
	bool mouseClicked = e.type == sf::Event::MouseButtonPressed and e.mouseButton.button == sf::Mouse::Left;

	if (mouseClicked and slider.getGlobalBounds().contains(e.mouseButton.x, e.mouseButton.y)) {
		dragging = true;
		mouseRectOffset.x = e.mouseButton.x - slider.getGlobalBounds().left - slider.getOrigin().x;
		mouseRectOffset.y = e.mouseButton.y - slider.getGlobalBounds().left - slider.getOrigin().y;
	}

	else if (e.type == sf::Event::MouseButtonReleased and e.mouseButton.button == sf::Mouse::Left) {
		dragging = false;
	}

	else if (e.type == sf::Event::MouseMoved) {
		mouseX = e.mouseMove.x;
		mouseY = e.mouseMove.y;
	}
}

void VolumeSlider::setSliderTexture(const sf::Texture *texure){
	//If the texture is nullptr, assign the nullptr to the slider, which will remove it.
	if (!texure)
		slider.setTexture(texure);
	
	//Otherwise, assign the user's texture to the slider
	else {
		sliderTexture = *texure;
		slider.setTexture(&sliderTexture);
	}
}

void VolumeSlider::setSliderColor(const sf::Color &color){
	slider.setFillColor(color);
}

void VolumeSlider::setVolumeColor(const sf::Color &color){
	leftEndPoint.setFillColor(color);
	volumeLevelColoring.setFillColor(color);
}

sf::Music &VolumeSlider::getMusic() {
	return music;
}
