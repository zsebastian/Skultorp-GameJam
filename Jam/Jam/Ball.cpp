#include "Ball.h"
#include "Display.h"

Ball::Ball()
	:mMass(0.f)
{
	mTempCircle.setRadius(50.f);
	mTempCircle.setFillColor(sf::Color::Green);
	setPosition(sf::Vector2f(200, 200));
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