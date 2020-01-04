#pragma once
#include <SFML/Graphics.hpp>

/*
* Function to return the position of the right edge of a drawable SFML object
*/
template<class Type>
float getRightEdge(const Type &object) {
	return object.getPosition().x + object.getGlobalBounds().width;
}

/*
* Function to return the position of the bottom edge of a drawable SFML object
*/
template<class Type>
float getBottomEdge(const Type &object) {
	return object.getPosition().y + object.getGlobalBounds().height;
}

/*
* Function to return the position of the center of a drawable SFML object
*/
template<class Type>
sf::Vector2f getCenterPosition(const Type &object) {
	return object.getPosition() + sf::Vector2f(object.getGlobalBounds().width / 2.f, object.getGlobalBounds().height / 2.f);
}