#ifndef ENTITYMANAGER_H
#define ENTITYMANAGER_H

#include <vector>
#include <memory>

class Display;
class Entity;
class EntityManager
{
public:
	typedef std::vector<std::shared_ptr<Entity> > EntityVec;

	EntityManager();
	~EntityManager();

	void update(); 
	void render(Display& display);
private:
	EntityVec mEntities;
};

#endif