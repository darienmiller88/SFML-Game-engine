 #include "RectangularButton.h"
#include "..//Math stuff//Math.h"

RectangularButton::RectangularButton(const sf::Text &text, bool isUsingRounded) : Button(text), isUsingRounded(isUsingRounded){
	changeButtonSize();
	makeRoundedButton(isUsingRounded, { 0.f, 0.f });
}

RectangularButton::RectangularButton(const sf::Text &text, const sf::Vector2f &position, bool isUsingRounded,
const dm::ColorPack &cPack) : Button(text), defaultColor(std::get<0>(cPack)), hoverColor(std::get<1>(cPack)), 
clickColor(std::get<2>(cPack)), isUsingColors(true), isUsingTextures(false), isUsingRounded(isUsingRounded)
{
	buttonBody.setFillColor(defaultColor);
	changeButtonSize();
	makeRoundedButton(isUsingRounded, position);
}

RectangularButton::RectangularButton(const sf::Text &text, const dm::TexturePack &tPack, const sf::Vector2f &position, 
bool isUsingRounded) : Button(text), defaultTexture(std::get<0>(tPack)), hoverTexture(std::get<1>(tPack)),
clickTexture(std::get<2>(tPack)), isUsingColors(false), isUsingTextures(true), isUsingRounded(isUsingRounded)
{
	buttonBody.setTexture(&defaultTexture); 
	changeButtonSize();
	makeRoundedButton(isUsingRounded, position);
}

void RectangularButton::setResizingScale(const sf::Vector2f &newScale){
	if (newScale.x < 1 or newScale.y < 1) {
		std::cerr << "Scales cannot be less than 1!\n";
		return;
	}

	resizingScale = newScale;
	changeButtonSize();
}

void RectangularButton::drawButton(sf::RenderWindow &window){
	window.draw(buttonBody);
	window.draw(buttonText);
	window.draw(buttonLeft);
	window.draw(buttonRight);
}

void RectangularButton::setText(const std::string &newText){
	buttonText.setString(newText);
	buttonText.setOrigin(buttonText.getGlobalBounds().width / 2.f, buttonText.getGlobalBounds().height / 2.f + 3);

	//Once you change the text of the button, check to see if the button is in resizing mode, and resize the button using
	//the current resize scale.
	if (isResizing)
		changeButtonSize();
}

void RectangularButton::setPosition(const sf::Vector2f &position){
	makeRoundedButton(isUsingRounded, position);	
	buttonText.setPosition(getCenterPosition(buttonBody));
}

void RectangularButton::setTextCharactersize(uint32_t charSize){
	buttonText.setCharacterSize(charSize);
	buttonText.setOrigin(buttonText.getGlobalBounds().width / 2.f, buttonText.getGlobalBounds().height / 2.f + 3);

	if (isResizing) 
		changeButtonSize();
}

void RectangularButton::setColorPack(const dm::ColorPack &colorPack){
	defaultColor = std::get<0>(colorPack);
	hoverColor = std::get<1>(colorPack);
	clickColor = std::get<2>(colorPack);
	isUsingColors = true;
	isUsingTextures = false;
}

void RectangularButton::setTexturePack(const dm::TexturePack &texturePack){
	defaultTexture = std::get<0>(texturePack);
	hoverTexture = std::get<1>(texturePack);
	clickTexture = std::get<2>(texturePack);
	isUsingColors = false;
	isUsingTextures = true;
}

void RectangularButton::setOutlineThickness(float thickness){
	buttonBody.setOutlineThickness(thickness);
}

void RectangularButton::setOutlineColor(const sf::Color &color){
	buttonBody.setOutlineColor(color);
}

const sf::Vector2f &RectangularButton::getButtonSize() const{
	return buttonBody.getSize();
}

const sf::RectangleShape &RectangularButton::getButtonBody() const{
	return buttonBody;
}

void RectangularButton::handleOnClickEvent(sf::Event e, const sf::RenderWindow &window){
	sf::Vector2f mousePosition = window.mapPixelToCoords(sf::Mouse::getPosition(window));
	bool isMouseHovering = buttonBody.getGlobalBounds().contains(mousePosition);
	bool isMouseHoveringSides = buttonLeft.getGlobalBounds().contains(mousePosition) || buttonRight.getGlobalBounds().contains(mousePosition);
	static bool wasClicked = false; 
	bool isMouseReleased = e.type == sf::Event::MouseButtonReleased;

	//isClicked = (e.type == sf::Event::MouseButtonPressed and e.mouseButton.button == sf::Mouse::Left);
	//if the texture pack is empty (the color pack was initialized instead, and vice versa) and the mouse is
	//hovering over the button, AND the mousebutton was clicked, change the color of the button the third color, which is
	//the button clicked color/texture
	if ((isMouseHovering or isMouseHoveringSides) and 
		e.type == sf::Event::MouseButtonPressed and e.mouseButton.button == sf::Mouse::Left) {
		if (isUsingColors) {
			buttonBody.setFillColor(clickColor);
			buttonLeft.setFillColor(clickColor);
			buttonRight.setFillColor(clickColor);
		}
		else if (isUsingTextures) {
			buttonBody.setTexture(&clickTexture);
			buttonLeft.setTexture(&clickTexture);
			buttonRight.setTexture(&clickTexture);
		}
		wasClicked = true;
	}
	else if ((isMouseHovering or isMouseHoveringSides) and wasClicked and isMouseReleased) {
		wasClicked = false;
		callBack();
	}
	else if ((isMouseHovering or isMouseHoveringSides) and isUsingColors) {
		buttonBody.setFillColor(hoverColor);
		buttonLeft.setFillColor(hoverColor);
		buttonRight.setFillColor(hoverColor);
	}
	else if ((isMouseHovering or isMouseHoveringSides) and isUsingTextures) {
		buttonBody.setTexture(&hoverTexture);
		buttonLeft.setTexture(&hoverTexture);
		buttonRight.setTexture(&hoverTexture);
	}
	else if (isUsingTextures) {
		buttonBody.setTexture(&defaultTexture);
		buttonLeft.setTexture(&defaultTexture);
		buttonRight.setTexture(&defaultTexture);
	}
	else {
		buttonBody.setFillColor(defaultColor);
		buttonLeft.setFillColor(defaultColor);
		buttonRight.setFillColor(defaultColor);
	}
}

void RectangularButton::changeButtonSize(){
	float newWidth = buttonText.getGlobalBounds().width * resizingScale.x;
	float newHeight = buttonText.getGlobalBounds().height * resizingScale.y;

	buttonBody.setSize({ newWidth, newHeight });
	buttonText.setPosition(getCenterPosition(buttonBody));
}

void RectangularButton::makeRoundedButton(bool isUsingRounded, const sf::Vector2f &position){
	if (isUsingRounded) {
		buttonLeft.setRadius(buttonBody.getSize().y / 2.f);
		buttonRight.setRadius(buttonBody.getSize().y / 2.f);
		buttonLeft.setPosition(position);
		buttonBody.setPosition(getCenterPosition(buttonLeft).x, position.y);
		buttonRight.setPosition(getRightEdge(buttonBody) - getHalfSize(buttonRight).x, position.y);
	}
	else
		buttonBody.setPosition(position);
}
