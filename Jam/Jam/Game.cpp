#include "Game.h"
#include "Cat.h"
#include "Ball.h"
#include "tinyxml2.h"
#include "Utility.h"

Game::Game()
{
	entities.pushEntity(std::make_shared<Cat>(sf::Vector2f(50.f, 50.f), 10.f));

	/*entities.pushEntity(std::make_shared<Ball>(sf::Vector2f(200.f, 200.f), 200.f, 100.f));
	entities.pushEntity(std::make_shared<Ball>(sf::Vector2f(100.f, 100.f), 100.f, 50.f));
	entities.pushEntity(std::make_shared<Ball>(sf::Vector2f(700.f, 100.f), 100.f, 50.f));
	entities.pushEntity(std::make_shared<Ball>(sf::Vector2f(100.f, 500.f), 100.f, 50.f));
	entities.pushEntity(std::make_shared<Ball>(sf::Vector2f(700.f, 500.f), 100.f, 50.f));*/

	loadLevel("data/levels/test.xml");

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

void Game::loadLevel(const std::string& filename)
{
	tinyxml2::XMLDocument doc;
	doc.LoadFile(filename.c_str());

	tinyxml2::XMLElement* level = doc.FirstChildElement("level");
	tinyxml2::XMLElement* balls = level->FirstChildElement("balls");

	for(tinyxml2::XMLElement* ball = balls->FirstChildElement("ball"); ball; ball = ball->NextSiblingElement())
	{
		sf::Vector2f position;
		position.x = Util::fromString<float>(ball->Attribute("x"));
		position.y = Util::fromString<float>(ball->Attribute("y"));
		float mass = Util::fromString<float>(ball->Attribute("mass"));
		float radius = Util::fromString<float>(ball->Attribute("radius"));
		int index = Util::fromString<int>(ball->Attribute("index"));

		entities.pushEntity(std::make_shared<Ball>(position, mass, radius, index));
	}
}