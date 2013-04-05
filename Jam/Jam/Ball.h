#ifndef BALL_H
#define BALL_H

#include "Entity.h"

class Ball : public Entity
{
public:
	Ball();
	virtual ~Ball();

	virtual void setPosition(const sf::Vector2f& position);
	virtual void setMass(float mass);
	virtual void update();
	virtual void render();
	virtual void onCollision(std::shared_ptr<Entity> entity);

	virtual sf::Vector2f getPosition();
	virtual float getMass();
private:
	sf::Vector2f mPosition;
	float mMass;
};

#endif