#include "Slider.h"
#include "sfml game engine/Math stuff/Math.h"
#include <iostream>

Slider::Slider(const sf::RenderWindow &window) : 
BAR_WIDTH(20.f), 

MIN_LENGTH(BAR_WIDTH / 10.f),

MAX_LENGTH(static_cast<float>(window.getSize().y) / 2.f),

upArrow(BAR_WIDTH / 5.f, 3), downArrow(BAR_WIDTH / 5.f, 3), currentDirection(SliderState::NOT_MOVING),
onClickSlideUp([]() {}), onClickSlideDown([]() {}), currentSlidingSpeed(0){
	//First, we will set the sizes of all of our bar components
	sliderBackground.setSize({ BAR_WIDTH, static_cast<float>(window.getSize().y) });
	verticalSlider.setSize({ BAR_WIDTH - 5.f, sliderBackground.getSize().y / 2.f });
	boxForDownArrow.setSize({ BAR_WIDTH, BAR_WIDTH });
	boxForUpArrow.setSize({ BAR_WIDTH, BAR_WIDTH });

	//Afterwards, we will set all of the colors. We'll start off by setting the background and the boxes to a light gray, 
	//and the other components to a darker gray.
	sliderBackground.setFillColor(sf::Color(220, 220, 220));
	boxForUpArrow.setFillColor(sf::Color(220, 220, 220));
	boxForDownArrow.setFillColor(sf::Color(220, 220, 220));
	verticalSlider.setFillColor(sf::Color(140, 140, 140));
	upArrow.setFillColor(sf::Color(140, 140, 140));
	downArrow.setFillColor(sf::Color(140, 140, 140));
	

	//Set the origins of the arrows to their center. This will make it easier to position them appropiately below.
	upArrow.setOrigin(getHalfSize(upArrow));
	downArrow.setOrigin(getHalfSize(downArrow));

	//Flip the triangle upside down.
	downArrow.setScale(downArrow.getScale().x, -1);

	//Here, we will set the positions of all the components 
	boxForUpArrow.setPosition(static_cast<float>(window.getSize().x) - BAR_WIDTH, 0.f);
	boxForDownArrow.setPosition(boxForUpArrow.getPosition().x, (float)window.getSize().y - BAR_WIDTH);
	sliderBackground.setPosition(static_cast<float>(window.getSize().x) - BAR_WIDTH, 0.f);
	verticalSlider.setPosition(getCenterPosition(sliderBackground).x - getHalfSize(verticalSlider).x, 
		getBottomEdge(boxForUpArrow));
	upArrow.setPosition(getCenterPosition(boxForUpArrow));
	downArrow.setPosition(getCenterPosition(boxForDownArrow));

}

void Slider::drawSlider(sf::RenderWindow &window){
	if (dragging) {
		verticalSlider.setPosition(verticalSlider.getPosition().x, mouseY - mouseRectOffset.y);
		constrainSlider();

		switch (currentDirection){
			case SliderState::NOT_MOVING:
				//std::cout << "not moving\n";
				break;
			case SliderState::SLIDING_UP:
				onClickSlideUp();
				break;
			case SliderState::SLIDING_DOWN:
				onClickSlideDown();
				break; 
		}
		currentDirection = SliderState::NOT_MOVING;
	}

	
	if (arrowIsClicked) {
		verticalSlider.move(0.f, currentSlidingSpeed);	
		constrainSlider();
	}	

	window.draw(sliderBackground);
	window.draw(boxForDownArrow);
	window.draw(boxForUpArrow);
	window.draw(verticalSlider);
	window.draw(upArrow);
	window.draw(downArrow);
}

float Slider::getSliderLength() const{
	return verticalSlider.getSize().y;
}

void Slider::constrainSlider(){
	//First, we will constrain the position to being below the top box and above the bottom box.
	float newPosition = constrain(verticalSlider.getPosition().y, getBottomEdge(boxForUpArrow),
		boxForDownArrow.getPosition().y - verticalSlider.getSize().y);

	//Afterwards, set the constrained position to the vertical slider
	verticalSlider.setPosition(verticalSlider.getPosition().x, newPosition);
}

void Slider::changeSliderLengthBy(float additionalLength){
	float newLength = constrain(verticalSlider.getSize().y + additionalLength, MIN_LENGTH, MAX_LENGTH);
	verticalSlider.setSize({ verticalSlider.getSize().x, newLength });
}

void Slider::eventHandler(const sf::RenderWindow &window, sf::Event e){
	sf::Vector2f mousePosition = window.mapPixelToCoords(sf::Mouse::getPosition(window));
	bool mouseClicked = (e.type == sf::Event::MouseButtonPressed and e.mouseButton.button == sf::Mouse::Left);
	bool mouseHoveringSlider = verticalSlider.getGlobalBounds().contains(mousePosition);
	bool mouseHoveringTop = boxForUpArrow.getGlobalBounds().contains(mousePosition);
	bool mouseHoveringBottom = boxForDownArrow.getGlobalBounds().contains(mousePosition);

	//If the user clicks the mouse while the pointer is on the up arrow, and while the slider is NOT touching it,
	//change the color and call the callback.
	if (mouseClicked and mouseHoveringTop and getBottomEdge(boxForUpArrow) != verticalSlider.getPosition().y) {
		arrowIsClicked = true;
		upArrow.setFillColor(sf::Color::White);
		boxForUpArrow.setFillColor(sf::Color(80, 80, 80));//darkish gray
		currentSlidingSpeed = -0.25f;
	}
	
	//If the user clicks the mouse while the pointer is on the down arrow, and while the slider is NOT touching it,
	//change the color and call the callback.
	else if (mouseClicked and mouseHoveringBottom and boxForDownArrow.getPosition().y != getBottomEdge(verticalSlider)) {
		arrowIsClicked = true;
		downArrow.setFillColor(sf::Color::White);
		boxForDownArrow.setFillColor(sf::Color(80, 80, 80));
		currentSlidingSpeed = 0.25f;
	}

	//If the mouse pointer is on t he up arrow while the slider is NOT touching it, change the color of the box.
	else if (mouseHoveringTop and getBottomEdge(boxForUpArrow) != verticalSlider.getPosition().y) {
		boxForUpArrow.setFillColor(sf::Color(180, 180, 180));
		arrowIsClicked = false;
	}
		
	//Do the same for when the mouse pointer is on the down arrow
	else if (mouseHoveringBottom and boxForDownArrow.getPosition().y != getBottomEdge(verticalSlider)) {
		boxForDownArrow.setFillColor(sf::Color(180, 180, 180));
		arrowIsClicked = false;
	}
		
	//if the mouse pointer is above the slider, change the color to a darker gray
	else if (mouseHoveringSlider)
		verticalSlider.setFillColor(sf::Color(80, 80, 80));
	
	//If none of the other events are taking place, set the color of all the components back to their default values
	else {
		sliderBackground.setFillColor(sf::Color(220, 220, 220));
		boxForUpArrow.setFillColor(sf::Color(220, 220, 220));
		boxForDownArrow.setFillColor(sf::Color(220, 220, 220));
		verticalSlider.setFillColor(sf::Color(140, 140, 140));
		upArrow.setFillColor(sf::Color(140, 140, 140));
		downArrow.setFillColor(sf::Color(140, 140, 140));
	}

	updateSlider(e, mouseClicked);
}

void Slider::updateSlider(sf::Event e, bool mouseClicked) {	
	if (mouseClicked and verticalSlider.getGlobalBounds().contains(e.mouseButton.x, e.mouseButton.y)) {
		dragging = true;
		mouseRectOffset.x = e.mouseButton.x - verticalSlider.getPosition().x;
		mouseRectOffset.y = e.mouseButton.y - verticalSlider.getPosition().y;
		verticalSlider.setFillColor(sf::Color(50, 50, 50));//dark gray
	}

	else if (e.type == sf::Event::MouseButtonReleased and e.mouseButton.button == sf::Mouse::Left) {
		dragging = false;
	}

	//Mouse Moved in window
	else if (e.type == sf::Event::MouseMoved) {
		previousY = mouseY;
		mouseX = e.mouseMove.x;
		mouseY = e.mouseMove.y;
	}

	changeDirection();	
}

void Slider::changeDirection() {
	if (mouseY > previousY) {
		currentDirection = SliderState::SLIDING_DOWN;
	}
	else if (mouseY < previousY) {
		currentDirection = SliderState::SLIDING_UP;
	}
	else {
		currentDirection = SliderState::NOT_MOVING;
	}
}

void Slider::setOnClickForSlideUp(std::function<void()> onClick){
	onClickSlideUp = onClick;
}

void Slider::setOnClickForSlideDown(std::function<void()> onClick){
	onClickSlideDown = onClick;
}