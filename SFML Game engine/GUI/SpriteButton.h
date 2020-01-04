#pragma once
#include "Button.h"

class SpriteButton : public dm::Button<sf::Sprite> {
	public:
		/*
		* \brief Constructor to create a button using a tuple containing three different textures.
		*
		* @param text - The text that will reside on the button. 
		* @param tPack - A tuple that will contain all of the textures relevant to the button functionality.
		* - The first element is the default texture of the button when the mouse pointer is not interacting with it
		* - The second element is the texture the button will change to when the mouse pointer hovers over it
		* - The third element is the texture the button will change to when the mouse pointer clicks on it
		*/
		SpriteButton(const sf::Text &text, const dm::TexturePack &tPack, const sf::Vector2f &position);
		
		/*
		* \brief function to handle the various interactions the mouse pointer will have with the button. For optimal use,
		* place this function call inside of the while(window.pollEvent(e)) {} loop so each event happens exactly once.
		*
		* \param e - the event to be handled
		* \param window - the main loop window.
		*/
		void handleOnClickEvent(sf::Event e, const sf::RenderWindow &window) override;

		/*
		* \brief function to scale the button's width and height by a fixed amount.
		*
		* \param newScale the factor in which the button will be scaled by. newScale.x is what the button's width will be 
		* multiplied and scaled up by, and newScale.y is what the button's height will be scaled up by .
		*/
		void setResizingScale(const sf::Vector2f &newScale);
		
		void setText(const std::string &newText) override;
		void setTextCharactersize(uint32_t charSize) override;
		void setDefaultTextureToSmooth(bool isUsingSmooth);
		void sethoverTextureToSmooth(bool isUsingSmooth);
		void setClickTextureToSmooth(bool isUsingSmooth);
	private:
		void changeButtonSize();
	private:
		sf::Texture defaultTexture, hoverTexture, clickTexture;
};