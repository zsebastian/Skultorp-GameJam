#ifndef ENTITYMANAGER_H
#define ENTITYMANAGER_H

#include <vector>
#include <queue>
#include <memory>
#include "GravityField.h"
#include "Editor.h"

class Cat;
class Display;
class Entity;
class Camera;
class EntityManager
{
public:
	typedef std::vector<std::shared_ptr<Entity> > EntityVec;
	typedef std::queue<std::string> StrQueue;

	EntityManager();
	~EntityManager();

	void update(); 
	void render(Display& display);

	void pushEntity(std::shared_ptr<Entity>);
	void popEntity(std::shared_ptr<Entity> entity);
	void clear();
	void loadLevel();
	void loadLevelList();
	std::string getLevelFilename();
private:
	EntityVec mEntities;
	StrQueue mLevelList;
	GravityField mGravityField;
	Editor mEditor;

	void checkLevelCleared();

	std::shared_ptr<Cat> mCat;
	int mNumberOfYarn;

	Camera* mCamera;
};

#endif