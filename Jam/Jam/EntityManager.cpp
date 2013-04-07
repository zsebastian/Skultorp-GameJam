#include "EntityManager.h"
#include "Display.h"
#include "Entity.h"
#include "Utility.h"
#include "Ball.h"
#include "tinyxml2.h"
#include "Cat.h"
#include "LooseEnd.h"
#include <iostream>

EntityManager::EntityManager()
	:mEditor(this)
	,mCat(NULL)
	,mNumberOfYarn(0)
	,mCamera(NULL)
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

	checkLevelCleared();

	//Update editor
	mEditor.update();

	//Restart level if cat is 'dead'
	if(!mCat->isAlive())
		loadLevel();
}

void EntityManager::render(Display& display)
{
	mCamera = &display.getCamera();

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
}

void EntityManager::loadLevel()
{
	clear();

	if (mLevelList.empty())
		return; //if no next level don't load it!

	tinyxml2::XMLDocument doc;
	doc.LoadFile(mLevelList.front().c_str());

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

		auto ballEntity = std::make_shared<Ball>(position, mass, radius, index);

		//Add ball
		pushEntity(ballEntity);

		tinyxml2::XMLElement* looseEnd = ball->FirstChildElement("looseEnd");
		float angle = Util::fromString<float>(looseEnd->Attribute("angle"));

		//Add loose end
		pushEntity(std::make_shared<LooseEnd>(ballEntity, angle));
	}

	//Add cat
	tinyxml2::XMLElement* cat = level->FirstChildElement("cat");
	sf::Vector2f position;
	position.x = Util::fromString<float>(cat->Attribute("x"));
	position.y = Util::fromString<float>(cat->Attribute("y"));
	pushEntity(std::make_shared<Cat>(position, 10.f));

	//Set camera to Cat's position
	if(mCamera)
	{
		mCamera->setPosition(position);
		mCamera->setRotation(0.f);
	}
}

void EntityManager::loadLevelList()
{
	tinyxml2::XMLDocument doc;
	doc.LoadFile("data/levels.xml");

	tinyxml2::XMLElement* levels = doc.FirstChildElement("levels");
	for(tinyxml2::XMLElement* level = levels->FirstChildElement("level"); level; level = level->NextSiblingElement())
		mLevelList.push("data/levels/" + std::string(level->Attribute("name"))+".xml");
}

std::string EntityManager::getLevelFilename()
{
	return mLevelList.front();
}

void EntityManager::checkLevelCleared()
{
	if(mLevelList.empty())
		return;

	if(mCat != NULL)
	{
		if(mCat->getNextYarn() == 5)
		{
			mLevelList.pop();
			if(!mLevelList.empty())
				loadLevel();
			else
			{
				//Win!
				std::cout << "Win!";
			}
		}
	}
}