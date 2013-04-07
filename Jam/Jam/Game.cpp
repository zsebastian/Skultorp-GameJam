#include "Game.h"
#include "Cat.h"
#include "Ball.h"
#include "LooseEnd.h"
#include "Utility.h"
#include "TextureManager.h"

Game::Game(StateManager& stateManager)
	:State(stateManager)
{
	//Load textures
	TextureManager::loadTexture("data/yarn_ball_blue.png");
	TextureManager::loadTexture("data/yarn_ball_red.png");
	TextureManager::loadTexture("data/yarn_ball_yellow.png");
	TextureManager::loadTexture("data/yarn_ball_green.png");
	TextureManager::loadTexture("data/yarn_ball_goal.png");
	TextureManager::loadTexture("cat.png");
	TextureManager::loadTexture("data/looseend.png");

	mBackgroundTexture.loadFromFile("data/background.png");
	mBackgroundTexture.setSmooth(true);
	mBackgroundSprite.setTexture(mBackgroundTexture);
	sf::FloatRect bounds = mBackgroundSprite.getLocalBounds();
	mBackgroundSprite.setOrigin(bounds.width/2.f, bounds.height/2.f);
	mBackgroundSprite.setScale(1.f, 1.f);

	entities.loadLevelList();
	entities.loadLevel();
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