#ifndef ENTITY_H
#define ENTITY_H

#include <memory>
#include <SFML/System/Vector2.hpp>

class Display;
class Entity
{
public:
	virtual ~Entity(){}

	virtual void setPosition(const sf::Vector2f& position) = 0;
	virtual void setMass(float mass) = 0;
	virtual void update() = 0;
	virtual void render(Display& display) = 0;
	virtual void onCollision(std::shared_ptr<Entity> entity) = 0;

	virtual sf::Vector2f getPosition() = 0;
	virtual float getMass() = 0;
};

#endif