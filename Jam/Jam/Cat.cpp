#include "Cat.h"
#include "Display.h"
#include "Ball.h"
#include "Utility.h"

Cat::Cat(const sf::Vector2f& position, float mass, float radius)
	:mMass(mass)
	,mGravityVector(0.f, 0.f)
	,mPosition(position)
	,mMoveSpeed(0,0)
	,mWalkSpeed(3)
	,mCanJump(false)
	,mJumping(false)
	,mMaxJumpPower(10.f)
	,mCurrentJumpPower(0)
	,mJumpDecelaration(0.7f)
	,mAnimations("cat.png")
{
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
	mMoveSpeed = sf::Vector2f();

	jump();
	jumping();
	walk();
	move();

	mTempShape.setPosition(mPosition);
}

void Cat::move()
{
	mPosition += mGravityVector + mMoveSpeed;
}

void Cat::walk()
{
	mRightVector = Util::getNormal(mGravityVector);
	mRightVector = Util::normalize(mRightVector);
	mRightVector *= mWalkSpeed;

	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
	{
		mMoveSpeed += mRightVector;
	}
	else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
	{
		mMoveSpeed -= mRightVector;
	}
}

void Cat::jump()
{
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && mCanJump)
	{
		mJumping = true;
		mCanJump = false;
		mCurrentJumpPower = mMaxJumpPower;
		mJumpDirection = -mGravityVector;
		mStandsOn.clear();
	}
}

void Cat::jumping()
{
	if(mJumping)
	{
		mMoveSpeed += Util::normalize(mJumpDirection) * mCurrentJumpPower;

		mCurrentJumpPower -= mJumpDecelaration;
		if(mCurrentJumpPower <= 0.f)
		{
			mCurrentJumpPower = 0.f;
			mJumping = false;
		}
	}
<<<<<<< HEAD
=======
	//Apply gravity
	mPosition += mGravityVector;
>>>>>>> 3d7d814fad1542d92c831394213b25e8824af7cf
}

void Cat::render(Display& display)
{
	sf::CircleShape tempShape;
	tempShape.setOrigin(mRadius, mRadius);
	tempShape.setPosition(mPosition);
	tempShape.setFillColor(sf::Color::Red);
	tempShape.setRadius(mRadius);	
	display.render(tempShape);

	//display.render(mAnimations.getSprite(mPosition));
}

void Cat::onCollision(std::shared_ptr<Entity> entity)
{
	std::shared_ptr<Ball> ball = std::dynamic_pointer_cast<Ball>(entity);

	if (ball)
	{
		mStandsOn.push_back(ball);

		sf::Vector2f dVec = mPosition - ball->getPosition();
		dVec = Util::normalize(dVec);
		float distance = ball->getRadius() + mRadius;
		dVec = dVec * distance;
		mPosition = ball->getPosition() + dVec;
		mCanJump = true;
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


std::vector<std::shared_ptr<Ball>>& Cat::standsOnPlanets()
{
	return mStandsOn;
}

void Cat::resetStandsOn()
{
	for (auto iter = mStandsOn.begin(); iter != mStandsOn.end(); ++iter)
	{
		(*iter)->resetMass();
	}

	mStandsOn.clear();
}