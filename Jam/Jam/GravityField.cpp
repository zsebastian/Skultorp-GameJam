#include "GravityField.h"
#include <SFML\System\Vector2.hpp>
#include <algorithm>
#include <cmath>
#include "Ball.h"
#include "Cat.h"

GravityField::GravityField(float gravityForce)
	:mGravityForce(gravityForce)
{

}

void GravityField::addObject(std::shared_ptr<Ball> ball)
{
	mBalls.push_back(ball);
}

void GravityField::addObject(std::shared_ptr<Cat> cat)
{
	mCat = cat;
}

void GravityField::removeObject(std::shared_ptr<Ball> ball)
{
	auto pred = [&ball](std::shared_ptr<Ball> testball) {return testball.get() == ball.get();};

	mBalls.erase(
		std::remove_if(mBalls.begin(), mBalls.end(), pred),
		mBalls.end());
}

void GravityField::removeObject(std::shared_ptr<Cat> cat)
{
	if (mCat == cat)
		mCat == nullptr;
}


void GravityField::update()
{
	sf::Vector2f sumGravVector(0, 0);

	for (auto ball: mBalls)
	{
		//F = G(m1*m2)/r^2
		float F = ((mGravityForce) * ball->getMass() * mCat->getMass()) / distance(ball->getPosition(), mCat->getPosition());
		sf::Vector2f gravVector = F * normalize(ball->getPosition() - mCat->getPosition());
		sumGravVector += gravVector;
	}

	mCat->setGravityVector(sumGravVector);
}

float GravityField::distance(sf::Vector2f v0, sf::Vector2f v1)
{
	float dx = v0.x - v1.x;
	float dy = v0.y - v1.y;
	return std::abs(std::sqrt((dx*dx) + (dy*dy)));
}

sf::Vector2f GravityField::normalize(sf::Vector2f v)
{
	return (v * (1 / length(v)));
}

float GravityField::length(sf::Vector2f v)
{
	return std::abs(std::sqrt((v.x*v.x) + (v.y*v.y)));
}