#ifndef STATEMANAGER_H
#define STATEMANAGER_H

#include <memory>
#include "State.h"
#include <vector>
#include <SFML\System\Clock.hpp>
class Display;

class StateManager
{
public:
	StateManager();

	void pushState(std::shared_ptr<State> state);

	void update();
	void render(Display&);
public:
	std::vector<std::shared_ptr<State>> mStateStack;

	//clock is used for timestepping
	sf::Clock clock;

	float msElapsed;
	const float msUpdateRate;

};

#endif