#include "Game.h"
#include "Cat.h"
#include "Ball.h"
#include "LooseEnd.h"
#include "tinyxml2.h"
#include "Utility.h"

Game::Game()
{
	entities.pushEntity(std::make_shared<Cat>(sf::Vector2f(50.f, 50.f), 10.f));

	std::shared_ptr<Ball> ball = std::make_shared<Ball>(sf::Vector2f(200.f, 200.f), 200.f, 100.f);
	entities.pushEntity(ball);
	entities.pushEntity(std::make_shared<LooseEnd>(ball, 180));
	entities.pushEntity(std::make_shared<LooseEnd>(ball, 90));
	entities.pushEntity(std::make_shared<LooseEnd>(ball, 45));
	entities.pushEntity(std::make_shared<LooseEnd>(ball, 245));

	loadLevel("data/levels/some_level.xml");
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

		entities.pushEntity(std::make_shared<Ball>(position, mass, radius));
	}
}