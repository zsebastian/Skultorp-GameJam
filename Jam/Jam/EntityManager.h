#ifndef ENTITYMANAGER_H
#define ENTITYMANAGER_H

#include <vector>
#include <memory>
#include "GravityField.h"
#include "Editor.h"

class Cat;
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
	void popEntity(std::shared_ptr<Entity> entity);
	void clear();
	void loadLevel(const std::string& filename);
private:
	EntityVec mEntities;
	GravityField mGravityField;
	Editor mEditor;

	void checkLevelCleard();

	std::shared_ptr<Cat> mCat;
	int mNumberOfYarn;
};

#endif