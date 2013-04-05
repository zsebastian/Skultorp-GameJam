#ifndef CAT_H
#define CAT_H

#include "Entity.h"
#include <SFML/Graphics/CircleShape.hpp>

class Cat : public Entity
{
public:
	Cat(const sf::Vector2f& position = sf::Vector2f(), float mass = 0.f);

	virtual ~Cat();

	virtual void setPosition(const sf::Vector2f& position);
	virtual void setMass(float mass);
	virtual void update();
	virtual void render(Display& display);
	virtual void onCollision(std::shared_ptr<Entity> entity);
	void setGravityVector(const sf::Vector2f& gravityVector);

	virtual sf::Vector2f getPosition() const;
	virtual float getMass() const;
private:
	sf::Vector2f mPosition;
	sf::Vector2f mGravityVector;
	float mMass;

	sf::CircleShape mTempShape;
};

#endif