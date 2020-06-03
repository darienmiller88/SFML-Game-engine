#pragma once
#include <SFML/Graphics.hpp>
#include <memory>
#include <iostream>
#include <functional>
#include "..//Math stuff//Math.h"

namespace dm {
	using TexturePack = std::tuple<sf::Texture, sf::Texture, sf::Texture>;
	using ColorPack = std::tuple<sf::Color, sf::Color, sf::Color>;

	/*
	* Abstract Class to define a clickable button, which is will be inherited from by other button class that will allow users
	* to create different types of buttons. The class is templated to allow each subclass to instantiate it as the proper 
	* button type (sf::RectangleShape, sf::Sprite, etc.), and pass in the proper pack type (dm::ColorPack
	* or dm::TexturePack).
	*/
	template<class ButtonType>
	class Button{
		public:

			/*
			* \brief Constructor to initialize the button text.
			*
			* @param text - The text that will reside on the button. 
			*/
			Button(const sf::Text &text) : buttonText(text), callBack([](){}), isResizing(true), resizingScale(1.5f, 1.5f){
				buttonText.setOrigin(buttonText.getGlobalBounds().width / 2.f, buttonText.getGlobalBounds().height / 2.f + 3);
			}

			void setOnclickEvent(std::function<void()> func) {
				callBack = func;
			}

			const std::string &getButtonText() const {
				return buttonText.getString();
			}

			const sf::Vector2f &getResizingScale() const {
				return resizingScale;
			}

			/*
			* \brief function to determine whether or not the button will automatically resize once the text is either
			* changed or the text character size is altered.
			*
			* \param isResizing boolean to determine if button resizes automatically. True for yes, false for no. By default,
			* the button enables automatic resizing.
			*/
			void enableResizing(bool isResizing) {
				this->isResizing = isResizing;
			}

			void setTextColor(const sf::Color &color) {
				buttonText.setFillColor(color);
			}

			virtual void drawButton(sf::RenderWindow& window) {
				window.draw(buttonBody);
				window.draw(buttonText);
			}

			virtual void setText(const std::string& newText) {
				buttonText.setString(newText);
				buttonText.setOrigin(buttonText.getGlobalBounds().width / 2.f, buttonText.getGlobalBounds().height / 2.f);
			}

			virtual void setTextCharactersize(uint32_t charSize) {
				buttonText.setCharacterSize(charSize);
				buttonText.setOrigin(buttonText.getGlobalBounds().width / 2.f, buttonText.getGlobalBounds().height / 2.f);
			}

			virtual void setResizingScale(const sf::Vector2f &newScale) = 0;
			virtual void handleOnClickEvent(sf::Event e, const sf::RenderWindow& window) = 0;	
		protected:
			bool isResizing;
			sf::Vector2f resizingScale;
			sf::Text buttonText;
			std::function<void()> callBack;
			ButtonType buttonBody;
	};
}