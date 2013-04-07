#include "Game.h"
#include "Cat.h"
#include "Ball.h"
#include "LooseEnd.h"
#include "tinyxml2.h"
#include "Utility.h"

Game::Game(StateManager& stateManager)
	:State(stateManager)
{
	entities.pushEntity(std::make_shared<Cat>(sf::Vector2f(50.f, 50.f), 10.f));

	mBackgroundTexture.loadFromFile("data/background.png");
	mBackgroundSprite.setTexture(mBackgroundTexture);
	mBackgroundSprite.setPosition(-1000.f, -1000.f);
	mBackgroundSprite.setScale(1.f, 1.f);
}

void Game::render(Display& display)
{
	Camera cam = display.getCamera();

	display.setToDefaultView();

	display.render(mBackgroundSprite);

	display.getCamera() = cam;

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