#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include <memory>
#include "../Math stuff/Math.h"
#include "StateManager.h"

class GameState{
	public:
		GameState(const sf::Vector2u& windowSize) : WINDOW_SIZE(windowSize) {

		}

		virtual ~GameState() {

		}

		//display the state to the screen
		virtual void drawState(sf::RenderWindow &window) = 0;

		virtual void update(float deltaTime) = 0;

		//function to allow a gamestate to pause while another gamestate is running
		virtual void pause() = 0;
		
		//since we can pause game states, we also need to be able to unpause/resume them!
		virtual void unpause() = 0;

		//Purely virtual function to allow subclasses of the State class to handle mouse and keyboard input, and change states from
		//within their own state (for example, a title screen stating containing a menu with settings, play game, quit, etc.)
		virtual void handleInput(StateManager &manager, const sf::Event &e, const sf::RenderWindow &window, float deltaTime) = 0;
		
	protected:
		//Utility function to read and error handle a file into a texture.
		template<class SFML_OBJECT>
		void tryToReadFile(SFML_OBJECT &texture, const std::string &fileName) {
			if (!texture.loadFromFile(fileName)) {
				std::cout << "Cannot read from file!\n";
				exit(1);
			}
		}

		//function to allow gamestates to check if the mouse cursor is touching an SMFL object
		template<class SFML_OBJECT>
		bool isMouseTouching(const SFML_OBJECT &clickableObject, const sf::RenderWindow &window) const {
			sf::Vector2f mousePosition = window.mapPixelToCoords(sf::Mouse::getPosition(window));

			return clickableObject.getGlobalBounds().contains(mousePosition);
		}

		//function to allow gamestates to check if an SFML object was clicked or not
		template<class SFML_OBJECT>
		bool isEntityClicked(const SFML_OBJECT &clickableObject, const sf::RenderWindow &window) const {
			return (sf::Mouse::isButtonPressed(sf::Mouse::Left) and isMouseTouching(clickableObject, window));
		}

		//Unlike the SFML "isKeyPressed" function, this one will only check too see a key is pressed ONCE.
		bool isKeyPressed(const sf::Keyboard::Key &key, const sf::Event &e) {
			return e.type == sf::Event::KeyPressed and e.key.code == key;
		}
		
		const sf::Vector2u WINDOW_SIZE;
};