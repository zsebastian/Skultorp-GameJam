#ifndef CAT_H
#define CAT_H

#include "Entity.h"
#include <SFML/Graphics/CircleShape.hpp>

class Cat : public Entity
{
public:
	Cat(const sf::Vector2f& position = sf::Vector2f(), float mass = 10.f, float radius = 20.f);

	virtual ~Cat();

	virtual void setPosition(const sf::Vector2f& position);
	virtual void setMass(float mass);
	virtual void setRadius(float radius);
	virtual void update();
	virtual void render(Display& display);
	virtual void onCollision(std::shared_ptr<Entity> entity);
	void setGravityVector(const sf::Vector2f& gravityVector);

	virtual sf::Vector2f getPosition() const;
	virtual float getMass() const;
	virtual float getRadius() const;
private:
	sf::Vector2f mPosition;
	sf::Vector2f mGravityVector;
	float mMass;
	float mRadius;

	sf::CircleShape mTempShape;
};

#endif