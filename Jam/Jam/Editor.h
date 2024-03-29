#ifndef EDITOR_H
#define EDITOR_H

#include <vector>
#include "EventHandler.h"
#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/System/Vector2.hpp>

class Display;
class Entity;
class EntityManager;
class Editor
{
public:
	typedef std::vector<std::shared_ptr<Entity> > EntityVec;

	Editor(EntityManager* entityManager = 0);
	~Editor();

	void pushEntity(std::shared_ptr<Entity> entity);
	void popEntity(std::shared_ptr<Entity> entity);
	void clear();

	void update();
	void render(Display& display);
private:
	struct YarnType
	{
		YarnType(int index = 0, float radiusModifer = 1.f, float massModifier = 1.f) 
			:index(index),radiusModifer(radiusModifer),massModifier(massModifier) {};
		int index;
		float radiusModifer;
		float massModifier;
	};

	std::vector<YarnType> mYarnTypes;
	YarnType mSelectedYarn;

	EntityVec mEntities;
	std::shared_ptr<Entity> mCurrentEntity;
	bool mLockedOnEntity;
	int mCurrentIndex;

	EntityManager* mEntityManager;

	sf::CircleShape mPotentialEntity;
	sf::Vector2f mMousePosition;

	EventHandler mEventHandler;
	void onButtonDown(sf::Event&);
	void onButtonUp(sf::Event&);
	void onMouseMove(sf::Event&);
	void onKeyDown(sf::Event&);
	void onMouseWheel(sf::Event&);

	void saveLevel(const std::string& filename);
};

#endif