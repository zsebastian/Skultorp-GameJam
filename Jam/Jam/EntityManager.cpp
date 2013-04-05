#include "EntityManager.h"
#include "Display.h"
#include "Entity.h"

EntityManager::EntityManager()
{

}

EntityManager::~EntityManager()
{
	while(mEntities.
}

void EntityManager::update()
{
	//Update entities
	for(EntityVec::iterator i = mEntities.begin(); i != mEntities.end(); i++)
		(*i)->update();

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
	for(EntityVec::iterator i = mEntities.begin(); i != mEntities.end(); i++)
		(*i)->render(display);
}