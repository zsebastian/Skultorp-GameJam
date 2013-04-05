#include "EntityManager.h"
#include "Display.h"
#include "Entity.h"

EntityManager::EntityManager()
{

}

EntityManager::~EntityManager(){}

void EntityManager::update()
{
	//Update entities
	for(auto entity : mEntities)
		entity->update();

	mGravityField.update();

	//Check for collisions
	for(EntityVec::size_type i = 0; i < mEntities.size(); i++)
	{
		for(EntityVec::size_type j = i+1; j < mEntities.size(); j++)
		{
			//Check for intersection

			/*mEntities[i]->onCollision(mEntities[j]);
			mEntities[j]->onCollision(mEntities[i]);*/
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