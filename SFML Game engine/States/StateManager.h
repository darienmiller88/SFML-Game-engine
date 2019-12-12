#pragma once
#include "GameState.h"
#include "../Utilities/FrameRate.h"
#include <stack>
#include <SFML/Graphics.hpp>
#include <memory>

class StateManager{
	public:
		StateManager(int windowWidth, int windowHeight, const std::string &title);
		void runGame();
		void quitGame();
		void pushState(const std::unique_ptr<GameState> &state);
		void changeState(const std::unique_ptr<GameState>& state);
		void popState();
	private:
		sf::Clock clock;
		FrameRate FPS;
		std::stack< std::unique_ptr<GameState> > states;
		bool gameIsRunning;
		sf::RenderWindow window;
};

