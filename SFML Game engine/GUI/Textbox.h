#pragma once
#include <SFML/Graphics.hpp>
#include <functional>

class Textbox{
	public:
		/**
		* \param initialSize - x will determine how tall the textbox, and y will determine how wide it is.
		* \param defaultText - The text that will reside on the textbox until it is clicked.
		*/
		Textbox(const sf::Vector2f &initialSize, const sf::Vector2f &position, const sf::Font &font, 
			const std::string &defaultText);
		void drawTextBox(sf::RenderWindow &window);
		void setTextColor(const sf::Color &textColor);//Set the color of the text to any desired colored.
		void setTypedText(const sf::Color &textColor);//Set the color of the text that will be typed.
		void setOutlineColor(const sf::Color &outlineColor);
		//Set the color that the textbox changes to when the moves hovers over it
		void setHoverColor(const sf::Color &hoverColor);
		
		//Assign a function that will be called once the enter key is pressed. Note that it MUST be a parameterless
		//void function, which was done for the sake of simplicity.
		void setOnEnterEvent(std::function<void()> callback);

		//This function is meant to be called inside of the while(window.pollEvent(e)){} loop. 
		void eventHandler(const sf::RenderWindow &window, sf::Event e);
		const std::string &getTypedWord() const;
	private:
		void drawCursor(sf::RenderWindow &window);
		void handleText(sf::Event e);
	private:
		const int FRAME_LIMIT;
		const float OUTLINE_THICKNESS;
		sf::Color hoverColor, defaultBoxColor, outlineColor, textColor, typedTextColor;
		int numFrames = 0;
		bool isTextBoxClicked = false, isCharLimitReached = false;
		sf::RectangleShape cursor, textBox;

		//"backgroundTextBox" will reside behind the actual textbox, and will be a different color to give the illusion
		//of an outline. This is accomplished by making is slightly larger, and leaving it transparent
		sf::RectangleShape backgroundTextBox;

		//text will hold the characters that the user will type in, and defaultText will contain the default text residing
		//on the text box.
		sf::Text typedText, defaultText;
		std::string word;
		std::function<void()> onEnterCallback;
};