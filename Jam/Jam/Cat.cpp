#include "Cat.h"
#include "Display.h"

Cat::Cat(const sf::Vector2f& position, float mass)
	:mMass(mass)
	,mGravityVector(0.f, 0.f)
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

void Cat::update()
{
	//Apply gravity
	mPosition += mGravityVector;
	mTempShape.setPosition(mPosition);

	mRightVector.x = mGravityVector.y;
	mRightVector.y = -mGravityVector.x;

	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
	{
		mPosition += mRightVector;
	}
	else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
	{
		mPosition -= mRightVector;
	}
}

void Cat::render(Display& display)
{
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