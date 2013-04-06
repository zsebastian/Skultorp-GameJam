#include "Ball.h"
#include "Display.h"
#include "Utility.h"

Ball::Ball(const sf::Vector2f& position, float mass, float radius)
	:mMass(mass)
	,mActualMass(mass)
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
	mTempCircle.setOrigin(radius, radius);
}

void Ball::update()
{
	//HOOOOOOOOW
	mActualMass += mMass / 500.f;

	if (mActualMass > mMass)
		mActualMass = mMass;
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
	return mActualMass;
}

float Ball::getRadius() const
{
	return mRadius;
}

void Ball::resetMass()
{
	mActualMass = 1.f;
}