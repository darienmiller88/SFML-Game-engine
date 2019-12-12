#pragma once
#include <SFML/Graphics.hpp>

class Timer {
	public:
		Timer();

		//This is meant to be run every frame inside of a loop, as it will continously call the other functions to start or stop the time.
		void runTimer();
		void reset();

		//These functions are meant to be called once!
		void startTimer();
		void stopTimer();

		//Get the current time.
		const sf::Time &getElaspedTime();
	private:
		enum class States { STOPPED, PAUSED, RUNNING };
		States currentState;
		bool wasPaused;
		sf::Time currentTime, lastTime, timeWhenPaused;
		sf::Clock clock;
};
