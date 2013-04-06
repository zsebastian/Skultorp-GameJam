#include "EntityManager.h"
#include "Display.h"
#include "Entity.h"
#include "Utility.h"

EntityManager::EntityManager()
{

}

EntityManager::~EntityManager(){}

void EntityManager::update()
{
	//Update gravity
	mGravityField.update();

	//Update entities
	for(auto entity : mEntities)
		entity->update();

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
}

void EntityManager::render(Display& display)
{
	//Render entities
	for(auto entity : mEntities)
		entity->render(display);
}

void EntityManager::pushEntity(std::shared_ptr<Entity> entity)
{
	mEntities.push_back(entity);
	mGravityField.addObject(entity);
}