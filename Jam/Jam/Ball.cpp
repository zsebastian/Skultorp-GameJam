#include "Ball.h"
#include "Display.h"

Ball::Ball()
	:mMass(0.f)
{

}

Ball::~Ball()
{
	
}

void Ball::setPosition(const sf::Vector2f& position)
{
	mPosition = position;
}

void Ball::setMass(float mass)
{
	mMass = mass;
}

void Ball::update()
{

}

void Ball::render(Display& display)
{

}

void Ball::onCollision(std::shared_ptr<Entity> entityy)
{

}

sf::Vector2f Ball::getPosition()
{
	return mPosition;
}

float Ball::getMass()
{
	return mMass;
}