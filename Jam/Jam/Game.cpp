#include "Game.h"
#include "Cat.h"
#include "Ball.h"
#include "LooseEnd.h"
#include "Utility.h"
#include "TextureManager.h"

Game::Game()
{
	//Load textures
	TextureManager::loadTexture("data/yarn_ball.png");
	TextureManager::loadTexture("data/yarn_ball_large.png");
	TextureManager::loadTexture("data/yarn_ball_small.png");
	TextureManager::loadTexture("cat.png");
	TextureManager::loadTexture("data/looseend.png");

	mBackgroundTexture.loadFromFile("data/background.png");
	mBackgroundTexture.setSmooth(true);
	mBackgroundSprite.setTexture(mBackgroundTexture);
	sf::FloatRect bounds = mBackgroundSprite.getLocalBounds();
	mBackgroundSprite.setOrigin(bounds.width/2.f, bounds.height/2.f);
	mBackgroundSprite.setScale(2.f, 2.f);

	entities.loadLevelList();
	entities.loadLevel();
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