#include "Game.h"
#include "Cat.h"
#include "Ball.h"
#include "LooseEnd.h"

Game::Game()
{
	entities.pushEntity(std::make_shared<Cat>(sf::Vector2f(50.f, 50.f), 10.f));

	std::shared_ptr<Ball> ball = std::make_shared<Ball>(sf::Vector2f(200.f, 200.f), 200.f, 100.f);
	entities.pushEntity(ball);
	entities.pushEntity(std::make_shared<LooseEnd>(ball, 180));
	entities.pushEntity(std::make_shared<LooseEnd>(ball, 90));
	entities.pushEntity(std::make_shared<LooseEnd>(ball, 45));
	entities.pushEntity(std::make_shared<LooseEnd>(ball, 245));

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