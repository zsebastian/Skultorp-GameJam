#ifndef LOOSEEND_H
#define LOOSEEND_H

#include "Entity.h"
#include <SFML\System\Vector2.hpp>
#include <SFML\Graphics\Sprite.hpp>
#include <SFML\Graphics\Texture.hpp>

class Ball;

class LooseEnd : public Entity
{
public:
	LooseEnd(std::shared_ptr<Ball> belongsTo, float positionAngle);

	virtual void setPosition(const sf::Vector2f& position) ;
	virtual void setMass(float mass);
	virtual void setRadius(float radius);
	virtual void update();
	virtual void render(Display& display);
	virtual void onCollision(std::shared_ptr<Entity> entity);

	virtual sf::Vector2f getPosition() const;
	virtual float getMass() const;
	virtual float getRadius() const;
	virtual sf::FloatRect getGlobalBounds() const;

	size_t getIndexValue() const;
private:
	sf::Vector2f mPosition;

	float mMass;
	float mRadius;
	float mPositionAngle;

	std::weak_ptr<Ball> mBelongsTo; 

	sf::Sprite mSprite;
	sf::Texture mTexture;

	size_t mIndexValue;

};

#endif