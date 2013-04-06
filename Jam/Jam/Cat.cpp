#include "Cat.h"
#include "Display.h"
#include "Ball.h"
#include "Utility.h"

Cat::Cat(const sf::Vector2f& position, float mass, float radius)
	:mMass(mass)
	,mGravityVector(0.f, 0.f)
	,mPosition(position)
{
	mStandingOn = nullptr;
	setRadius(20.f);

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
	sf::CircleShape tempShape;
	tempShape.setOrigin(mRadius, mRadius);
	tempShape.setPosition(mPosition);
	tempShape.setFillColor(sf::Color::Red);
	tempShape.setRadius(mRadius);	
	display.render(tempShape);
}

void Cat::onCollision(std::shared_ptr<Entity> entity)
{
	std::shared_ptr<Ball> ball = std::dynamic_pointer_cast<Ball>(entity);

	if (ball)
	{
		mStandingOn = ball;

		sf::Vector2f dVec = mPosition - ball->getPosition();
		dVec = Util::normalize(dVec);
		float distance = ball->getRadius() + mRadius;
		dVec = dVec * distance;
		mPosition = ball->getPosition() + dVec;
	}
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


std::shared_ptr<Ball> Cat::standsOnPlanet()
{
	return mStandingOn;
}