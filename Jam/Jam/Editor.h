#ifndef EDITOR_H
#define EDITOR_H

#include <vector>
#include <memory>
#include "EventHandler.h"

class Display;
class Entity;
class Editor : public EventHandler
{
public:
	typedef std::vector<std::shared_ptr<Entity> > EntityVec;

	Editor();
	~Editor();

	void pushEntity(std::shared_ptr<Entity> entity);

	void update();
	void render(Display& display);
private:
	EntityVec mEntities;

	void onButtonDown(sf::Event&);
};

#endif