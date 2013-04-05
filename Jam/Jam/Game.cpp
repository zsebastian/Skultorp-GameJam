#include "Game.h"

void Game::render(Display& display)
{
	entities.render(display);
}

void Game::update()
{
	entities.update();
}

bool isAlive()
{
	return true;
}