#include "Cat.h"
#include "Display.h"
#include "Ball.h"
#include "Utility.h"
#include <string>

Cat::Cat(const sf::Vector2f& position, float mass, float radius)
	:mMass(mass)
	,mGravityVector(0.f, 0.f)
	,mPosition(position)
	,mMoveSpeed(0,0)
	,mWalkSpeed(3)
	,mCanJump(false)
	,mJumping(false)
	,mMaxJumpPower(7.f)
	,mCurrentJumpPower(0)
	,mJumpDecelaration(0.15f)
	,mAnimations("cat.png")
	,mLeftDir(false)
	,mSpriteDown(0.f, 1.f)
{
	setRadius(40.f);

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

	rotate();
	jump();
	jumping();
	walk();
	move();

	mTempShape.setPosition(mPosition);
	mYarn.updatePosition(mPosition, !mCanJump);

	if (mYarn.intersect(mPosition, mRadius))
	{
		mTempShape.setFillColor(sf::Color::Blue);
	}
	else
	{
		mTempShape.setFillColor(sf::Color::Red);
	}
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

	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right) && mAnimations.getCurrentAnimation() != "jump")
	{
		mLeftDir = false;
		if(mCanJump && mAnimations.getCurrentAnimation() != "inair")
		{
			mAnimations.setCurrentAnimation("walk");
		}
		mMoveSpeed += mRightVector;
	}
	else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && mAnimations.getCurrentAnimation() != "jump")
	{
		mLeftDir = true;
		if(mCanJump && mAnimations.getCurrentAnimation() != "inair")
		{
			mAnimations.setCurrentAnimation("walk");
		}
		mMoveSpeed -= mRightVector;
	}
	
	if(!sf::Keyboard::isKeyPressed(sf::Keyboard::Right) && !sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
	{
		if(mCanJump && mAnimations.getCurrentAnimation() == "walk")
		{
			mAnimations.setCurrentAnimation("idle");
		}
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
		mAnimations.setCurrentAnimation("jump");
	}
}

void Cat::jumping()
{
	if(mJumping && mAnimations.getCurrentAnimation() == "inair")
	{
		mMoveSpeed += Util::normalize(mJumpDirection) * mCurrentJumpPower;

		mCurrentJumpPower -= mJumpDecelaration;
		if(mCurrentJumpPower <= 0.f)
		{
			mCurrentJumpPower = 0.f;
			mJumping = false;
		}
	}
}

void Cat::rotate()
{
	mTargetAngle = Util::angle(mGravityVector) - 90;
	float spriteRotation = mSprite.getRotation();

	float shortestDist = mTargetAngle - spriteRotation;
	while(shortestDist < -180)
	{
		shortestDist += 360;
	}
	while(shortestDist > 180)
	{
		shortestDist -= 360;
	}

	float rotateSpeed = 0.5f;

	if(!mCanJump)
	{
		rotateSpeed = 0.1;
	}
	mAnimations.setRotation(shortestDist * rotateSpeed);

}

void Cat::render(Display& display)
{
	mSprite = mAnimations.getSprite(mPosition);

	if(mLeftDir)
	{
		mSprite.scale(-1.f, 1.f);
	}

	mSprite.scale(0.4f, 0.4f);

	//Set camera position
	display.getCamera().setPosition(mPosition);
	
	mYarn.render(display);

	//Set camera rotation
	float camRot = mSprite.getRotation() - display.getCamera().getRotation();
	
	while(camRot < -180) camRot += 360;
	while(camRot > 180) camRot -= 360;

	if(mCanJump)
		display.getCamera().rotate(camRot*0.03);

	display.render(mSprite);
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
		
		if(mCanJump && mAnimations.getCurrentAnimation() == "inair")
		{
			mAnimations.setCurrentAnimation("land");
		}

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

sf::FloatRect Cat::getGlobalBounds() const
{
	return sf::FloatRect(mPosition.x - mRadius, mPosition.y - mRadius, mPosition.x + mRadius, mPosition.y + mRadius);
}