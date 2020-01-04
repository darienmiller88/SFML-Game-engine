#include "RectangularButton.h"
#include "UtilityFunctions.h"

RectangularButton::RectangularButton(const sf::Text &text, const dm::ColorPack& cPack, const sf::Vector2f &position) : 
Button(text), defaultColor(std::get<0>(cPack)), hoverColor(std::get<1>(cPack)), clickColor(std::get<2>(cPack)), 
isUsingColors(true), isUsingTextures(false){
	buttonBody.setFillColor(defaultColor);
	buttonBody.setPosition(position);
	changeButtonSize();
}

RectangularButton::RectangularButton(const sf::Text &text, const dm::TexturePack &tPack, const sf::Vector2f &position) : 
Button(text), defaultTexture(std::get<0>(tPack)), hoverTexture(std::get<1>(tPack)), clickTexture(std::get<2>(tPack)),
isUsingColors(false), isUsingTextures(true){
	buttonBody.setTexture(&defaultTexture); 
	buttonBody.setPosition(position);
	changeButtonSize();
}

void RectangularButton::setResizingScale(const sf::Vector2f &newScale){
	if (newScale.x < 1 or newScale.y < 1) {
		std::cerr << "Scales cannot be less than 1!\n";
		return;
	}

	resizingScale = newScale;
	changeButtonSize();
}

void RectangularButton::setText(const std::string &newText){
	buttonText.setString(newText);
	buttonText.setOrigin(buttonText.getGlobalBounds().width / 2.f, buttonText.getGlobalBounds().height / 2.f + 3);

	//Once you change the text of the button, check to see if the button is in resizing mode, and resize the button using
	//the current resize scale.
	if (isResizing)
		changeButtonSize();
}

void RectangularButton::setTextCharactersize(uint32_t charSize){
	buttonText.setCharacterSize(charSize);
	buttonText.setOrigin(buttonText.getGlobalBounds().width / 2.f, buttonText.getGlobalBounds().height / 2.f + 3);

	if (isResizing) 
		changeButtonSize();
}

void RectangularButton::setOutlineThickness(float thickness){
	buttonBody.setOutlineThickness(thickness);
}

void RectangularButton::setOutlineColor(const sf::Color &color){
	buttonBody.setOutlineColor(color);
}

const sf::Vector2f RectangularButton::getButtonSize() const{
	return buttonBody.getSize();
}

void RectangularButton::handleOnClickEvent(sf::Event e, const sf::RenderWindow &window){
	sf::Vector2f mousePosition = window.mapPixelToCoords(sf::Mouse::getPosition(window));
	bool isMouseHovering = buttonBody.getGlobalBounds().contains(mousePosition);
	bool isClicked = (e.type == sf::Event::MouseButtonPressed and e.mouseButton.button == sf::Mouse::Left);

	//if the texture pack is empty (the color pack was initialized instead, and vice versa) and the mouse is
	//hovering over the button, AND the mousebutton was clicked, change the color of the button the third color, which is
	//the button clicked color/texture
	if (isMouseHovering and isClicked and isUsingColors) {
		buttonBody.setFillColor(clickColor);
		callBack();
	}
	else if (isMouseHovering and isClicked and isUsingTextures) {
		buttonBody.setTexture(&clickTexture);
		callBack();
	}
	else if (isMouseHovering and isUsingColors)
		buttonBody.setFillColor(hoverColor);
	else if (isMouseHovering and isUsingTextures)
		buttonBody.setTexture(&hoverTexture);
	else if (isUsingTextures)
		buttonBody.setTexture(&defaultTexture);
	else
		buttonBody.setFillColor(defaultColor);
}

void RectangularButton::changeButtonSize(){
	float newWidth = buttonText.getGlobalBounds().width * resizingScale.x;
	float newHeight = buttonText.getGlobalBounds().height * resizingScale.y;

	buttonBody.setSize({ newWidth, newHeight });
	buttonText.setPosition(getCenterPosition(buttonBody));
}
