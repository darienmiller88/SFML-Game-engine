#include "SpriteButton.h"

SpriteButton::SpriteButton(const sf::Text &text, const dm::TexturePack &tPack, const sf::Vector2f &position) : 
Button(text), defaultTexture(std::get<0>(tPack)), hoverTexture(std::get<1>(tPack)), clickTexture(std::get<2>(tPack)) {
	defaultTexture.setSmooth(true);
	hoverTexture.setSmooth(true);
	clickTexture.setSmooth(true);
	buttonBody.setTexture(defaultTexture);
	buttonBody.setPosition(position);
	changeButtonSize();
}

void SpriteButton::handleOnClickEvent(sf::Event e, const sf::RenderWindow &window){
	sf::Vector2f mousePosition = window.mapPixelToCoords(sf::Mouse::getPosition(window));
	bool isMouseHovering = buttonBody.getGlobalBounds().contains(mousePosition);
	bool isClicked = (e.type == sf::Event::MouseButtonPressed and e.mouseButton.button == sf::Mouse::Left);

	//if the texture pack is empty (the color pack was initialized instead, and vice versa) and the mouse is
	//hovering over the button, AND the mousebutton was clicked, change the color of the button the third color, which is
	//the button clicked color/texture
	if (isMouseHovering and isClicked) {
		buttonBody.setTexture(clickTexture);
		callBack();
	}
	else if (isMouseHovering)
		buttonBody.setTexture(hoverTexture);
	else
		buttonBody.setTexture(defaultTexture);
}

void SpriteButton::setResizingScale(const sf::Vector2f &newScale){
	if (newScale.x < 1 or newScale.y < 1) {
		std::cerr << "Scales cannot be less than 1!\n";
		return;
	}

	resizingScale = newScale;
	changeButtonSize();
}

void SpriteButton::setText(const std::string &newText){
	buttonText.setString(newText);
	buttonText.setOrigin(buttonText.getGlobalBounds().width / 2.f, buttonText.getGlobalBounds().height / 2.f + 3);

	//Once you change the text of the button, check to see if the button is in resizing mode, and resize the button using
	//the current resize scale.
	if (isResizing)
		changeButtonSize();
}

void SpriteButton::setTextCharactersize(uint32_t charSize){
	buttonText.setCharacterSize(charSize);
	buttonText.setOrigin(buttonText.getGlobalBounds().width / 2.f, buttonText.getGlobalBounds().height / 2.f + 3);

	if (isResizing)
		changeButtonSize();
}

void SpriteButton::setDefaultTextureToSmooth(bool isUsingSmooth){
	defaultTexture.setSmooth(isUsingSmooth);
}

void SpriteButton::sethoverTextureToSmooth(bool isUsingSmooth){
	hoverTexture.setSmooth(isUsingSmooth);
}

void SpriteButton::setClickTextureToSmooth(bool isUsingSmooth){
	clickTexture.setSmooth(isUsingSmooth);
}

void SpriteButton::changeButtonSize(){
	float xScale = (buttonText.getGlobalBounds().width * resizingScale.x) / buttonBody.getGlobalBounds().width;
	float yScale = (buttonText.getGlobalBounds().height * resizingScale.y) / buttonBody.getGlobalBounds().height;

	std::cout << "xScale before change: " << xScale << " and yScale before change: " << yScale << "\n";

	xScale *= buttonBody.getScale().x;
	yScale *= buttonBody.getScale().y;

	std::cout << "xScale after change: " << xScale << " and yScale after change: " << yScale << "\n";

	//If the x or y scale of the button body is the same as the new scale calculated above, scale the other other one using
	//the new scale.
	if (xScale == buttonBody.getScale().x)
		buttonBody.setScale(buttonBody.getScale().x, yScale);
	else if (yScale == buttonBody.getScale().y)
		buttonBody.setScale(xScale, buttonBody.getScale().y);
	else
		buttonBody.setScale(xScale, yScale);
	buttonText.setPosition(getCenterPosition(buttonBody));
	std::cout << "button xScale: " << buttonBody.getScale().x << " and button yScale: " << buttonBody.getScale().y << "\n\n";

	/*if (newWidth != 1 or newHeight != 1) {
		buttonBody.setScale(newWidth, newHeight);
		buttonText.setPosition(getCenterPosition(buttonBody));
	}*/
}