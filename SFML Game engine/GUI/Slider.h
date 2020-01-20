#pragma once
#include <SFML/Graphics.hpp>
#include <functional>

class Slider{
	public:
		Slider(const sf::RenderWindow &window);
		void drawSlider(sf::RenderWindow &window);
		float getSliderLength() const;
		
		/**
		* \brief function to add or subtract a value from the length of the slider. There is a maximum and minimum
		* length, so if the parameter passed either bound, it will be set to that bound.
		* 
		* \param additionalLength The value to be added onto the slider length. If the value is negative, it will
		* decrease it, and if it is positive, it will increase it.
		*/
		void changeSliderLengthBy(float additionalLength);

		//This function is meant to be called inside of the while(window.pollEvent(e)){} loop. 
		void eventHandler(const sf::RenderWindow &window, sf::Event e);

		//Assign a function, be it a lambda, functor, or standard function to be called once the slider is moved upwards.
		void setOnClickForSlideUp(std::function<void()> onClick);

		//Assign a function, be it a lambda, functor, or standard function to be called once the slider is moved downwards.	
		void setOnClickForSlideDown(std::function<void()> onClick);

	private:
		void constrainSlider();
		void updateSlider(sf::Event e, bool mouseClicked);
		void changeDirection();
	private:
		const float BAR_WIDTH, MIN_LENGTH, MAX_LENGTH;
		float currentSlidingSpeed;
		enum class SliderState {
			NOT_MOVING, SLIDING_UP, SLIDING_DOWN	
		};

		SliderState currentDirection;

		//States for button/events
		bool mouseClicked = false;
		bool mouseInsideRect = false;
		bool dragging = false;
		bool arrowIsClicked = false;
		bool wasMouseMoved = false;

		sf::Vector2f mouseRectOffset;

		//Variables
		int previousX, previousY;
		int mouseX = 0;
		int mouseY = 0;

		sf::CircleShape upArrow, downArrow;
		sf::RectangleShape boxForUpArrow, boxForDownArrow, verticalSlider, sliderBackground;
		std::function<void()> onClickSlideUp, onClickSlideDown;
};

