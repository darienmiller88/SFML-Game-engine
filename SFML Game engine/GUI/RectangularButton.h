#pragma once
#include "Button.h"

class RectangularButton : public dm::Button<sf::RectangleShape>{
	public:
		RectangularButton(const sf::Text &text, bool isUsingRounded);

		/*
		* \brief Constructor to create a button using a tuple containing three different colors.
		*
		* \param text - The text that will reside on the button.
		* \param position - initial position of the button
		* \param colorPack - A tuple that will contain all of the colors relevant to the button functionality.
		* - The first element is the default color of the button when the mouse pointer is not interacting with it
		* - The second element is the color the button will change to when the mouse pointer hovers over it
		* - The third element is the color the button will change to when the mouse pointer clicks on it
		* This color pack will default to white for each element
		*/
		RectangularButton(const sf::Text &text, const sf::Vector2f &position, bool isUsingRounded,
			const dm::ColorPack &colorPack = {sf::Color::White, sf::Color::White , sf::Color::White });

		/*
		* \brief Constructor to create a button using a tuple containing three different textures.
		*
		* \param text - The text that will reside on the button.
		* \param tPack - A tuple that will contain all of the textures relevant to the button functionality.
		* - The first element is the default texture of the button when the mouse pointer is not interacting with it
		* - The second element is the texture the button will change to when the mouse pointer hovers over it
		* - The third element is the texture the button will change to when the mouse pointer clicks on it
		* \param position - initial position of the button
		*/
		RectangularButton(const sf::Text &text, const dm::TexturePack &tPack, const sf::Vector2f &position, bool isUsingRounded);

		/*
		* \brief function to handle the various interactions the mouse pointer will have with the button. For optimal use,
		* place this function call inside of the while(window.pollEvent(e)) {} loop so each event happens exactly once.
		*
		* \param e - the event to be handled
		* \param window - the main loop window.
		*/
		void handleOnClickEvent(sf::Event e, const sf::RenderWindow &window) override;

		/*
		* \brief function to determine how big the button is relative to the text on top of it.
		*
		* \param newScale vector to determine how big the scale is, x being how much wider the button is than the text,
		* and y being how much taller the button is. The scale defaults to (2, 2).
		*/
		void setResizingScale(const sf::Vector2f &newScale) override;

		void drawButton(sf::RenderWindow &window) override;
		void setText(const std::string &newText) override;
		void setPosition(const sf::Vector2f &position);
		void setTextCharactersize(uint32_t charSize) override;
		void setColorPack(const dm::ColorPack &colorPack);
		void setTexturePack(const dm::TexturePack &texturePack);
		void setOutlineThickness(float thickness);
		void setOutlineColor(const sf::Color &color);
		const sf::Vector2f &getButtonSize() const;
		const sf::RectangleShape &getButtonBody() const;
	private:
		void changeButtonSize();
		void makeRoundedButton(bool isUsingRounded, const sf::Vector2f &position);
	private:
		bool isUsingColors, isUsingTextures, isUsingRounded;
		sf::Texture defaultTexture, hoverTexture, clickTexture;
		sf::Color defaultColor, hoverColor, clickColor;
		sf::CircleShape buttonLeft, buttonRight;
};