#include "GravityField.h"
#include <SFML\System\Vector2.hpp>
#include <algorithm>
#include <cmath>
#include "Ball.h"
#include "Cat.h"
#include "Utility.h"

GravityField::GravityField(float gravityForce, float terminalVelocity)
	:mGravityForce(gravityForce)
	,mTerminalVelocity(terminalVelocity)
{

}

void GravityField::addObject(std::shared_ptr<Entity> entity)
{
	std::shared_ptr<Cat> cat = std::dynamic_pointer_cast<Cat>(entity);
	std::shared_ptr<Ball> ball = std::dynamic_pointer_cast<Ball>(entity);

	if (cat)
		mCats.push_back(cat);
	else if (ball)
		mBalls.push_back(ball);
}

void GravityField::removeObject(std::shared_ptr<Entity> entity)
{
	std::shared_ptr<Cat> cat = std::dynamic_pointer_cast<Cat>(entity);
	std::shared_ptr<Ball> ball = std::dynamic_pointer_cast<Ball>(entity);
	
	if (cat)
	{
		auto pred = [&cat](std::shared_ptr<Cat> testcat) {return testcat.get() == cat.get();};
		Util::eraseIf(mCats, pred);
	}
	else if (ball)
	{
		auto pred = [&ball](std::shared_ptr<Ball> testball) {return testball.get() == ball.get();};
		Util::eraseIf(mBalls, pred);
	}
	
}

void GravityField::update()
{
	for (auto cat = mCats.begin(); cat != mCats.end(); ++cat)
	{
		sf::Vector2f sumGravVector(0, 0);

		auto& standsOn = (*cat)->standsOnPlanets();

		if (!standsOn.empty())
		{
			for (auto ball = standsOn.begin(); ball != standsOn.end(); ++ball)
			{
				const float standingMultiplier = 1.0;
				sumGravVector += standingMultiplier * Util::normalize(calcGravity((*ball), (*cat)));
			}
			(*cat)->resetStandsOn();
		}
		else
		{
			for (auto ball = mBalls.begin(); ball != mBalls.end(); ++ball)
			{
				sumGravVector += calcGravity((*ball), (*cat));
			}
		}

		(*cat)->setGravityVector(sumGravVector);
	}
}

sf::Vector2f GravityField::calcGravity(const std::shared_ptr<Entity> e0, const std::shared_ptr<Entity> e1) const
{
	//F = G(m1*m2/r^2)
	float r = Util::distance(e0->getPosition(), e1->getPosition());
	float m1 = e0->getMass();
	float m2 = e1->getMass();
	float F = ((mGravityForce) * (( m1 * m2) / (r * r)));
	if (F > mTerminalVelocity)
		F = mTerminalVelocity;

	sf::Vector2f ret = F * Util::normalize(e0->getPosition() - e1->getPosition());
	return ret;
}