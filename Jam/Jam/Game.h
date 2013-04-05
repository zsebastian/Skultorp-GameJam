#ifndef GAME_H
#define GAME_H

#include "State.h"
#include "EntityManager.h"

class Game : public State
{
public:
	Game();
	virtual void render(Display&);
	virtual void update();
	virtual bool isAlive();
private:
	EntityManager entities;

};

#endif