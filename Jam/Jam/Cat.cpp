#include "Cat.h"
#include "Display.h"

Cat::Cat()
	:mMass(0.f)
	,mGravityVector(0.f, 0.f)
{
	mTempTexture.loadFromFile("data/cat.png");
	mTempSprite.setTexture(mTempTexture);
}

Cat::~Cat()
{

}

void Cat::setPosition(const sf::Vector2f& position)
{
	mPosition = position;
	mTempSprite.setPosition(mPosition);
}

void Cat::setMass(float mass)
{
	mMass = mass;
}

void Cat::update()
{
	//Apply gravity
	mPosition += mGravityVector;
}

void Cat::render(Display& display)
{
	display.render(mTempSprite);
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