#include "StateManager.h"
#include "../../TitleState.h"

StateManager::StateManager(int windowWidth, int windowHeight, const std::string &title) : gameIsRunning(true), 
window(sf::VideoMode(windowWidth, windowHeight), title, sf::Style::Close | sf::Style::Titlebar), FPS({ 0.f,0.f }) {
	states.push(std::make_unique<TitleState>(sf::Vector2u(windowWidth, windowHeight), *this));
}

void StateManager::runGame(){
	window.setFramerateLimit(60);
	while (window.isOpen() and gameIsRunning) {
		sf::Event e;
		while (window.pollEvent(e)) {
			if (e.type == sf::Event::Closed)
				window.close();
			states.top()->handleInput(*this, e, window);
		}
		
		window.clear();
		states.top()->update(FPS.getDeltaTime());
		states.top()->drawState(window);
		FPS.draw(window);
		window.display();
		FPS.calculate();
	}

	//clean up remaining gamestates!
	while (!states.empty())
		states.pop();
	std::cout << states.size() << std::endl;
}

void StateManager::quitGame(){
	gameIsRunning = false;  
}

void StateManager::pushState(const std::unique_ptr<GameState> &state){
	//if the stack is NOT empty, pause the current game state at the top of the stack
	if (!states.empty())
		states.top()->pause();

	//Afterwards, push the new state onto the stack.
	states.push(std::move(const_cast<std::unique_ptr<GameState>&>(state)));
}

void StateManager::changeState(const std::unique_ptr<GameState> &state){
	//To change the current state, first check to see if the stack is empty before popping.
	if (!states.empty())
		states.pop();

	//afterwards, replace that popped gamestate with the new one sent to this function.
	states.push(std::move(const_cast<std::unique_ptr<GameState>&>(state)));
}

void StateManager::popState(){
	//First, we check to see if the stack has game state in it before popping.
	if (!states.empty())
		states.pop();

	//After popping the stack, we check again to see if there remains another gamestate. If so, unpause it.
	if (!states.empty())
		states.top()->unpause();
}