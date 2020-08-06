#pragma once
#include "../Utilities/FrameRate.h"
#include <stack>
#include <SFML/Graphics.hpp>
#include <memory>

class GameState;

class StateManager{
	public:

		
		StateManager(const sf::Vector2u &windowSize, const std::string &title);

		/**
		* DESCRIPTION:
		*
		* This function will run the main game loop, starting with the initial game state passed to the constructor. 
		* Inside the event loop, which runs inside the main loop, the state that is on top of the stack will have its
		* "handleInput" function called, and then its update and draw methods called afterwards.
		*/
		void runGame();

		void quitGame();
		void pushState(std::unique_ptr<GameState> &&state);
		void changeState(std::unique_ptr<GameState> &&state);
		void popState();
	private:
		sf::Clock clock;
		FrameRate FPS;
		std::stack< std::unique_ptr<GameState> > states;
		bool gameIsRunning;
		sf::RenderWindow window;
};

