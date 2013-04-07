#ifndef ENTITY_H
#define ENTITY_H

#include <memory>
#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/Rect.hpp>

class Display;
class Entity
{
public:
	Entity() :mIsDead(false){};
	virtual ~Entity(){}

	virtual void setPosition(const sf::Vector2f& position) = 0;
	virtual void setMass(float mass) = 0;
	virtual void setRadius(float radius) = 0;
	virtual void update() = 0;
	virtual void render(Display& display) = 0;
	virtual void onCollision(std::shared_ptr<Entity> entity) = 0;

	virtual sf::Vector2f getPosition() const = 0;
	virtual float getMass() const = 0;
	virtual float getRadius() const = 0;
	virtual sf::FloatRect getGlobalBounds() const = 0;

	bool isDead() {return mIsDead;};

	void kill() {mIsDead = true;};
private:
	bool mIsDead;
};

#endif