#include "GameState.h"
#include "StateManager.h"

GameState::GameState(const sf::Vector2u &windowSize, StateManager &manager)
{
}

GameState::~GameState()
{
}

void GameState::changeState(StateManager &manager, const std::unique_ptr<GameState> &state){
	manager.changeState(std::move(const_cast<std::unique_ptr<GameState>&>(state)));
}

bool GameState::isMouseTouching(const sf::Sprite& clickableSprite, const sf::RenderWindow& window) const{
	sf::Vector2f mousePosition = window.mapPixelToCoords(sf::Mouse::getPosition(window));
	
	return clickableSprite.getGlobalBounds().contains(mousePosition);
}

bool GameState::isSpriteClicked(const sf::Sprite &clickableSprite, const sf::RenderWindow &window) const{
	//This statement will return true if the left mouse button was clicked, and if the mouse cursor was within the bounds of
	//the rectangle surrounding the Sprite object.
	return (sf::Mouse::isButtonPressed(sf::Mouse::Left) and isMouseTouching(clickableSprite, window));
}
