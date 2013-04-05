#include "Cat.h"
#include "Display.h"

Cat::Cat()
	:mMass(0.f)
{

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

}

void Cat::render(Display& display)
{

}

void Cat::onCollision(std::shared_ptr<Entity> entity)
{
	
}

sf::Vector2f Cat::getPosition()
{
	return mPosition;
}

float Cat::getMass()
{
	return mMass;
}