#include "Ball.h"
#include "Display.h"

Ball::Ball(const sf::Vector2f& position)
	:mMass(0.f)
	,mPosition(position)
{
	mTempCircle.setRadius(50.f);
	mTempCircle.setFillColor(sf::Color::Green);
	mTempCircle.setOrigin(mTempCircle.getRadius(), mTempCircle.getRadius());
}

Ball::~Ball()
{
	
}

void Ball::setPosition(const sf::Vector2f& position)
{
	mPosition = position;
	mTempCircle.setPosition(mPosition);
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
	mTempCircle.setPosition(mPosition);
	display.render(mTempCircle);
}

void Ball::onCollision(std::shared_ptr<Entity> entityy)
{

}

sf::Vector2f Ball::getPosition() const
{
	return mPosition;
}

float Ball::getMass() const
{
	return mMass;
}