#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include <memory>
#include "../Math stuff/Math.h"


class StateManager;

class GameState{
	public:
		GameState(const sf::Vector2u &windowSize, StateManager &manager);

		virtual ~GameState();

		//display the state to the screen
		virtual void drawState(sf::RenderWindow &window) = 0;

		virtual void update(float deltaTime) = 0;

		//function to allow a gamestate to pause while another gamestate is running
		virtual void pause() = 0;
		
		//since we can pause game states, we also need to be able to unpause/resume them!
		virtual void unpause() = 0;

		//Purely virtual function to allow subclasses of the State class to handle mouse and keyboard input, and change states from
		//within their own state (for example, a title screen stating containing a menu with settings, play game, quit, etc.)
		virtual void handleInput(StateManager &manager, const sf::Event &e, const sf::RenderWindow &window) = 0;
		
	protected:
		//Utility function to read and error handle a file into a texture.
		template<class SFML_OBJECT>
		void tryToReadFile(SFML_OBJECT &texture, const std::string &fileName);
		
		//Function to let each gamestate signal to the gamestate manager to switch to another gamestate.
		void changeState(StateManager &manager, const std::unique_ptr<GameState> &state);

		//function to allow gamestates to check if the mouse cursor is 
		bool isMouseTouching(const sf::Sprite &clickableSprite, const sf::RenderWindow &window) const;

		//function to allow gamestates to check if an sf::Text was clicked or not
		bool isSpriteClicked(const sf::Sprite &clickableSprite, const sf::RenderWindow &window) const;
		
};

template<class SFML_OBJECT>
inline void GameState::tryToReadFile(SFML_OBJECT &texture, const std::string &fileName){
	if (!texture.loadFromFile(fileName)) {
		std::cout << "Cannot read from file!\n";
		exit(1);
	}
}
