#include "Timer.h"

//test comment
Timer::Timer() : wasPaused(false), currentState(States::STOPPED){
}

void Timer::runTimer(){
	switch (currentState) {
		case States::PAUSED:
			stopTimer();
			break;
		case States::RUNNING:
			startTimer();
			break;
		default:
			reset();
	}
}

void Timer::reset(){
	currentTime = sf::Time::Zero;
	currentState = States::STOPPED;
	wasPaused = false;
	clock.restart();
}

void Timer::startTimer(){
	//If the timer was paused (stopTimer() was called), set the currentTime equal to the paused time + elapsed time. Otherwise set
	//the current time equal to the elapsed time.
	currentTime = (wasPaused) ? clock.getElapsedTime() + timeWhenPaused : clock.getElapsedTime();
	currentState = States::RUNNING;
}

void Timer::stopTimer(){
	currentTime += sf::Time::Zero;
	timeWhenPaused = currentTime;//Keep track of the moment in time when the timer was stopped!
	clock.restart();
	currentState = States::PAUSED;
	wasPaused = true;
}

const sf::Time &Timer::getElaspedTime(){
	return currentTime;
}
