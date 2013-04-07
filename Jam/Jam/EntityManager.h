#ifndef ENTITYMANAGER_H
#define ENTITYMANAGER_H

#include <vector>
#include <memory>
#include "GravityField.h"
#include "Editor.h"

class Cat;
class Display;
class Entity;
class EntityManager : public std::enable_shared_from_this<EntityManager>
{
public:
	typedef std::vector<std::shared_ptr<Entity> > EntityVec;

	EntityManager();
	~EntityManager();

	void update(); 
	void render(Display& display);

	void pushEntity(std::shared_ptr<Entity>);
	void popEntity(std::shared_ptr<Entity> entity);
private:
	std::shared_ptr<EntityManager> getptr(){return shared_from_this();}

	EntityVec mEntities;
	GravityField mGravityField;
	Editor mEditor;

	void checkLevelCleard();

	std::shared_ptr<Cat> mCat;
	int mNumberOfYarn;
};

#endif