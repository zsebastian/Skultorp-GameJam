#include "Game.h"
#include "Cat.h"
#include "Ball.h"
#include "LooseEnd.h"
#include "Utility.h"

Game::Game()
{
	entities.pushEntity(std::make_shared<Cat>(sf::Vector2f(50.f, 50.f), 10.f));

	std::shared_ptr<Ball> ball = std::make_shared<Ball>(sf::Vector2f(200.f, 200.f), 200.f, 100.f, 0);
	entities.pushEntity(ball);
	entities.pushEntity(std::make_shared<LooseEnd>(ball, 180));

	ball = std::make_shared<Ball>(sf::Vector2f(300.f, 200.f), 200.f, 100.f, 1);
	entities.pushEntity(ball);
	entities.pushEntity(std::make_shared<LooseEnd>(ball, 45));

	ball = std::make_shared<Ball>(sf::Vector2f(250.f, 300.f), 200.f, 100.f, 2);
	entities.pushEntity(ball);
	entities.pushEntity(std::make_shared<LooseEnd>(ball, 90));

	//loadLevel("data/levels/test.xml");

	mBackgroundTexture.loadFromFile("data/background.png");
	mBackgroundSprite.setTexture(mBackgroundTexture);
	mBackgroundSprite.setPosition(-1000.f, -1000.f);
	mBackgroundSprite.setScale(2.f, 2.f);
}

void Game::render(Display& display)
{
	display.render(mBackgroundSprite);
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