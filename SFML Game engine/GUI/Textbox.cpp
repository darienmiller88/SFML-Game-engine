#include "Textbox.h"
#include "..//Math stuff//Math.h"
#include <iostream>

//This comment is a change made from my desktop and pushed by git!
Textbox::Textbox(const sf::Vector2f &initialSize, const sf::Vector2f &position, const sf::Font &font,
const std::string &text) : textBox(initialSize), defaultText(text, font, FONT_SIZE), typedText("", font, FONT_SIZE), 
backgroundTextBox({initialSize.x + OUTLINE_THICKNESS, initialSize.y + OUTLINE_THICKNESS}),
cursor({ 1.f, initialSize.y * 0.75f }), onEnterCallback([]() {}), word("")
{
	//using a text object with only one character, we will use it to determine how wide one character is.
	characterWidth = sf::Text("d", font, FONT_SIZE).getGlobalBounds().width;
	maxCharLimit = textBox.getGlobalBounds().width / characterWidth;

	//set the colors of the text, textbox, and the "outline".
	defaultBoxColor = sf::Color(200, 200, 200);//light gray
	hoverColor = sf::Color::White;
	textColor = sf::Color(80, 80, 80);//dark gray
	outlineColor = sf::Color::Blue;
	typedTextColor = sf::Color::Black;

	//set the origin to the center instead of the top left corner
	backgroundTextBox.setOrigin(getHalfSize(backgroundTextBox));
	cursor.setOrigin(getHalfSize(cursor));

	textBox.setPosition(position);
	backgroundTextBox.setPosition(getCenterPosition(textBox));
	cursor.setPosition(textBox.getPosition().x + 10.f, getCenterPosition(textBox).y);
	defaultText.setPosition(getRightEdge(cursor), textBox.getPosition().y);
	typedText.setPosition(getRightEdge(cursor), textBox.getPosition().y);

	textBox.setFillColor(defaultBoxColor);
	backgroundTextBox.setFillColor(sf::Color(0, 0, 0, 0));
	cursor.setFillColor(sf::Color::Black);
	defaultText.setFillColor(textColor);
	typedText.setFillColor(sf::Color(0, 0, 0, 0));
	
	//std::cout << "size x: " << getSize(defaultText).x << " size y: " << getSize(defaultText).y << "\n";
	sf::Text temp("d", font, FONT_SIZE);
	temp.setScale(textBox.getSize().x / (getSize(temp).x * 2.f), textBox.getSize().y / (getSize(temp).y * 2.f));

	//Set the default text to half as tall as the textbox, and half as wide
	defaultText.setScale(temp.getScale());
	typedText.setScale(temp.getScale());	
}

void Textbox::drawTextBox(sf::RenderWindow &window){
	window.draw(backgroundTextBox);
	window.draw(textBox);
	window.draw(defaultText);
	window.draw(typedText);
	drawCursor(window);
}

void Textbox::setTextColor(const sf::Color &textColor){
	this->textColor = textColor;
}

void Textbox::setTypedText(const sf::Color &textColor){
	typedTextColor = textColor;
}

void Textbox::setCharacterLimit(int charLimit){
	this->charLimit = constrain(charLimit, 1, maxCharLimit);
}

void Textbox::setHoverColor(const sf::Color &hoverColor){
	this->hoverColor = hoverColor;
}

void Textbox::setOutlineColor(const sf::Color &outlineColor){
	this->outlineColor = outlineColor;
}

void Textbox::setOnEnterEvent(std::function<void()> callback){
	onEnterCallback = callback;
}

void Textbox::eventHandler(const sf::RenderWindow &window, sf::Event e){
	sf::Vector2f mousePosition = window.mapPixelToCoords(sf::Mouse::getPosition(window));
	bool mouseClicked = (e.type == sf::Event::MouseButtonPressed and e.mouseButton.button == sf::Mouse::Left);
	bool mouseHoveringTextBox = textBox.getGlobalBounds().contains(mousePosition);

	//Set the boolean to true if the user clicked the left mouse button while the mouse pointer is hovering over it.
	if (mouseClicked and mouseHoveringTextBox) {
		defaultText.setFillColor(sf::Color(0, 0, 0, 0));
		typedText.setFillColor(typedTextColor);
		numFrames = 0;
		isTextBoxClicked = true;
	}

	//However, if the user clicks on the left mouse button when the mouse pointer is NOT on the text box, set the boolean
	//to false so the cursor isn't drawn anymore.
	else if (mouseClicked and !mouseHoveringTextBox) {
		isTextBoxClicked = false;

		if(word.size() == 0)
			defaultText.setFillColor(textColor);
		textBox.setFillColor(defaultBoxColor);
		backgroundTextBox.setFillColor(sf::Color(0, 0, 0, 0));
	}

	//If the mouse pointer is sitting on top of the text box, or if the textbox was clicked, color the both the background
	//and the tetbox
	else if (mouseHoveringTextBox or isTextBoxClicked) {
		textBox.setFillColor(hoverColor);
		backgroundTextBox.setFillColor(outlineColor);
	}

	//If not other event is taking place, set the components to the default colors.
	else {
		textBox.setFillColor(defaultBoxColor);
		backgroundTextBox.setFillColor(sf::Color(0, 0, 0, 0));
	}


	handleText(e);
}

const std::string &Textbox::getTypedWord() const{
	return word;
}

void Textbox::drawCursor(sf::RenderWindow &window){
	numFrames++;

	//Draw the cursor onto the screen for n frames
	if (numFrames <= FRAME_LIMIT and isTextBoxClicked) {
		cursor.setFillColor(sf::Color::Black);
		window.draw(cursor);
		//std::cout << "drawing?\n";
	}

	//for another n frames, make the cursor completely transparent so that it appears as if it isn't being drawn.
	else if (numFrames <= FRAME_LIMIT * 2) {
		cursor.setFillColor(sf::Color(0, 0, 0, 0));
	}

	//Finally, once the number of frames exceeds n * 2, set it back to 0, and restart the process.
	else
		numFrames = 0;
}

void Textbox::handleText(sf::Event e){
	//If the user enters a key, and the unicode value of the character is in the desired range, append it onto the string
	//This range is important as it only includes character, and ignore keys like, space, backspace and delete.
	if (e.type == sf::Event::TextEntered and e.text.unicode > 32 and e.text.unicode < 127 and isTextBoxClicked) {
		defaultText.setFillColor(sf::Color(0, 0, 0, 0));
		typedText.setFillColor(typedTextColor);

		//std::cout << (char)e.text.unicode << "\n";
		//Once the text has reached the end of the textbox, prevent the user from typing anymore characters.
		if (word.size() < charLimit) {
			word += e.text.unicode;
		}
	}

	else if (e.type == sf::Event::KeyPressed and isTextBoxClicked) {
		if (e.key.code == sf::Keyboard::BackSpace and word.size() > 0) {
			word.pop_back();
			if (word.size() == 0)
				defaultText.setFillColor(textColor);
		}
			
		else if (e.key.code == sf::Keyboard::Space)
			word += " ";
		else if (e.key.code == sf::Keyboard::Enter) {
			onEnterCallback();
			word.clear();
		}
	}

	typedText.setString(word);

	//Every time a new character is appended onto the end of the string, move the cursor to the end of the text object
	cursor.setPosition(getRightEdge(typedText), cursor.getPosition().y);
}
