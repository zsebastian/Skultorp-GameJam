#include "EntityManager.h"
#include "Display.h"
#include "Entity.h"
#include "Utility.h"

EntityManager::EntityManager()
	:mEditor(this)
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