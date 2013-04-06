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
	for (auto cat: mCats)
	{
		sf::Vector2f sumGravVector(0, 0);
		for (auto ball: mBalls)
		{

			//F = G(m1*m2/r^2)
			float r = Util::distance(ball->getPosition(), cat->getPosition());
			float m1 = ball->getMass();
			float m2 =  cat->getMass();
			float F = ((mGravityForce) * (( m1 * m2) / (r * r)));
			if (F > mTerminalVelocity)
				F = mTerminalVelocity;

			sf::Vector2f gravVector = F * Util::normalize(ball->getPosition() - cat->getPosition());
			sumGravVector += gravVector;
		}
		cat->setGravityVector(sumGravVector);
	}
}
