#include "Game.h"
#include "Cat.h"
#include "Ball.h"
#include "LooseEnd.h"
#include "tinyxml2.h"
#include "Utility.h"

Game::Game()
{
	entities.pushEntity(std::make_shared<Cat>(sf::Vector2f(50.f, 50.f), 10.f));

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