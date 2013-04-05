#include "GravityField.h"
#include <SFML\System\Vector2.hpp>
#include <algorithm>

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


void update()
{
	sf::Vector2f gravVector;

}