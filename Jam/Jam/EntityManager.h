#ifndef ENTITYMANAGER_H
#define ENTITYMANAGER_H

#include <vector>
#include <memory>
#include "GravityField.h"
#include "Editor.h"

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

	void pushEntity(std::shared_ptr<Entity>);

private:
	EntityVec mEntities;
	GravityField mGravityField;
	Editor mEditor;
};

#endif