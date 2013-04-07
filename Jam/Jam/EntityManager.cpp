#include "EntityManager.h"
#include "Display.h"
#include "Entity.h"
#include "Utility.h"
#include "Ball.h"
#include "tinyxml2.h"
#include "Cat.h"

EntityManager::EntityManager()
	:mEditor(this),
	mCat(NULL),
	mNumberOfYarn(0)
{

}

EntityManager::~EntityManager(){}

void EntityManager::update()
{
	//Update gravity
	mGravityField.update();

	//Update entities
	for(auto iter = mEntities.begin(); iter != mEntities.end(); ++iter)
		(*iter)->update();

	//Check for collisions
	for(auto iter0 = mEntities.begin(); iter0 != mEntities.end(); ++iter0)
	{
		for(auto iter1 = iter0 + 1; iter1 != mEntities.end(); ++iter1)
		{
			//Check for intersection
			if (iter0 != iter1)
			{
				if (Util::testCircleCollision((*iter0)->getPosition(), (*iter0)->getRadius(), (*iter1)->getPosition(), (*iter1)->getRadius()))
				{
					(*iter0)->onCollision((*iter1));
					(*iter1)->onCollision((*iter0));
				}
			}
		}
	}

	Util::eraseIf(mEntities, [](std::shared_ptr<Entity> entity) {return entity->isDead();});

	//Update editor
	mEditor.update();
}

void EntityManager::render(Display& display)
{
	//Render entities
	for(auto iter = mEntities.begin(); iter != mEntities.end(); ++iter)
		(*iter)->render(display);

	//Render editor
	mEditor.render(display);
}

void EntityManager::pushEntity(std::shared_ptr<Entity> entity)
{
	std::shared_ptr<Cat> cat = std::dynamic_pointer_cast<Cat>(entity); 
	if(cat)
	{
		mCat = cat;
	}

	mEntities.push_back(entity);
	mGravityField.addObject(entity);
	mEditor.pushEntity(entity);
}

void EntityManager::popEntity(std::shared_ptr<Entity> entity)
{
	auto pred = [&entity](std::shared_ptr<Entity> someEntity) {return someEntity.get() == entity.get();};
	Util::eraseIf(mEntities, pred);

	mGravityField.removeObject(entity);
	mEditor.popEntity(entity);
}

void EntityManager::clear()
{
	mEntities.clear();
	mGravityField.clear();
	mEditor.clear();

	mCat = NULL;
}

void EntityManager::loadLevel(const std::string& filename)
{
	clear();

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

		pushEntity(std::make_shared<Ball>(position, mass, radius, index));
	}
}

void EntityManager::checkLevelCleard()
{
	if(mCat != NULL)
	{
		if(mCat->getNextYarn())
		{
			//win
		}
	}
}