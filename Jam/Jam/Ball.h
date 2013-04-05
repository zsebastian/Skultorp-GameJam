#ifndef BALL_H
#define BALL_H

#include "Entity.h"

#include <SFML/Graphics/CircleShape.hpp>

class Ball : public Entity
{
public:
	Ball(const sf::Vector2f& position = sf::Vector2f(), float mass = 0.f);
	virtual ~Ball();

	virtual void setPosition(const sf::Vector2f& position);
	virtual void setMass(float mass);
	virtual void update();
	virtual void render(Display& display);
	virtual void onCollision(std::shared_ptr<Entity> entity);

	virtual sf::Vector2f getPosition() const;
	virtual float getMass() const;
private:
	sf::Vector2f mPosition;
	float mMass;

	sf::CircleShape mTempCircle;
};

#endif