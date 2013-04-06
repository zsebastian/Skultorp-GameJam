#include "Game.h"
#include "Cat.h"
#include "Ball.h"

Game::Game()
{
	entities.pushEntity(std::make_shared<Cat>(sf::Vector2f(50.f, 50.f), 10.f));

	entities.pushEntity(std::make_shared<Ball>(sf::Vector2f(200.f, 200.f), 200.f, 100.f));
	entities.pushEntity(std::make_shared<Ball>(sf::Vector2f(100.f, 100.f), 100.f, 50.f));
	entities.pushEntity(std::make_shared<Ball>(sf::Vector2f(700.f, 100.f), 100.f, 50.f));
	entities.pushEntity(std::make_shared<Ball>(sf::Vector2f(100.f, 500.f), 100.f, 50.f));
	entities.pushEntity(std::make_shared<Ball>(sf::Vector2f(700.f, 500.f), 100.f, 50.f));
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