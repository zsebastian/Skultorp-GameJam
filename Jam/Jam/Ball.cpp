#include "Ball.h"
#include "Display.h"

Ball::Ball(const sf::Vector2f& position, float mass, float radius)
	:mMass(mass)
	,mPosition(position)
{
	setRadius(radius);
	mTempCircle.setFillColor(sf::Color::Green);
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

void Ball::setRadius(float radius)
{
	mRadius = radius;
	mTempCircle.setRadius(radius);
	mTempCircle.setOrigin(radius / 2.f, radius / 2.f);
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

float Ball::getRadius() const
{
	return mRadius;
}