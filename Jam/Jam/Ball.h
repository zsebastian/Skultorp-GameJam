#ifndef BALL_H
#define BALL_H

#include "Entity.h"

#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Sprite.hpp>

class Ball : public Entity
{
public:
	Ball(const sf::Vector2f& position = sf::Vector2f(), float mass = 10.f, float radius = 50.f, int index = 0);

	virtual ~Ball();

	virtual void setPosition(const sf::Vector2f& position);
	virtual void setMass(float mass);
	virtual void setRadius(float radius);
	virtual void update();
	virtual void render(Display& display);
	virtual void onCollision(std::shared_ptr<Entity> entity);

	virtual sf::Vector2f getPosition() const;
	virtual float getMass() const;
	virtual float getRadius() const;
	virtual sf::FloatRect getGlobalBounds() const;
	int getIndex() const;
	void resetMass();
private:
	sf::Vector2f mPosition;
	float mMass;
	float mRadius;
	float mActualMass;
	int mIndex;

	sf::Texture mTexture;
	sf::Sprite mSprite;
};

#endif