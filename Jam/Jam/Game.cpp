#include "Game.h"
#include "Cat.h"
#include "Ball.h"

Game::Game()
{
	entities.pushEntity(std::make_shared<Cat>());
	entities.pushEntity(std::make_shared<Ball>());
}

void Game::render(Display& display)
{
	entities.render(display);
}

void Game::update()
{
	entities.update();
}

bool Game::isAlive()
{
	return true;
}