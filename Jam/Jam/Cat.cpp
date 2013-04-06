#include "Cat.h"
#include "Display.h"

Cat::Cat(const sf::Vector2f& position, float mass, float radius)
	:mMass(mass)
	,mGravityVector(0.f, 0.f)
	,mPosition(position)
{
	mTempShape.setRadius(20.f);
	mTempShape.setFillColor(sf::Color::Red);

	setPosition(position);
}

Cat::~Cat()
{

}

void Cat::setPosition(const sf::Vector2f& position)
{
	mPosition = position;
}

void Cat::setMass(float mass)
{
	mMass = mass;
}

void Cat::setRadius(float radius)
{
	mRadius = radius;
}

void Cat::update()
{
	//Apply gravity
	mPosition += mGravityVector;
}

void Cat::render(Display& display)
{
	mTempShape.setPosition(mPosition);
	display.render(mTempShape);
}

void Cat::onCollision(std::shared_ptr<Entity> entity)
{
	
}

void Cat::setGravityVector(const sf::Vector2f& gravityVector)
{
	mGravityVector = gravityVector;
}

sf::Vector2f Cat::getPosition() const
{
	return mPosition;
}

float Cat::getMass() const
{
	return mMass;
}

float Cat::getRadius() const
{
	return mRadius;
}