#include "Cat.h"
#include "Display.h"
#include "Ball.h"
#include "Utility.h"
#include <string>
#include "LooseEnd.h"

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
	,mNextYarn(0)
{
	setRadius(40.f);

	setPosition(position);
	
	mThreadTextures.resize(3);
	mThreadTextures[0].loadFromFile("data/thread0.png");
	mThreadTextures[1].loadFromFile("data/thread1.png");
	mThreadTextures[2].loadFromFile("data/thread2.png");

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
	mTempShape.setRadius(radius);
	mTempShape.setOrigin(sf::Vector2f(radius, radius));
}

void Cat::update()
{
	mMoveSpeed = sf::Vector2f();

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
	mGravityAcc += mGravityVector;
	mPosition += mGravityAcc + mMoveSpeed;
}

void Cat::walk()
{
	mRightVector = Util::getNormal(mGravityVector);
	mRightVector = Util::normalize(mRightVector);
	mRightVector *= mWalkSpeed;

	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right) && mAnimations.getCurrentAnimation() != "jump" && mAnimations.getCurrentAnimation() != "land" )
	{
		mLeftDir = false;
		if(mCanJump && mAnimations.getCurrentAnimation() != "inair")
		{
			mAnimations.setCurrentAnimation("walk");
		}
		mMoveSpeed += mRightVector;
	}
	else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && mAnimations.getCurrentAnimation() != "jump" && mAnimations.getCurrentAnimation() != "land" )
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
	float spriteRotation = Util::angleInRange(mSprite.getRotation());

	float shortestDist = Util::shortestAngleDistance(mTargetAngle, spriteRotation);

	float rotateSpeed = 0.5f;

	if(!mCanJump)
	{
		rotateSpeed = 0.1f;
	}
	mAnimations.setRotation(shortestDist * rotateSpeed);
}

void Cat::render(Display& display)
{
	rotate();
	mSprite = mAnimations.getSprite(mPosition);

	if(mLeftDir)
	{
		mSprite.scale(-1.f, 1.f);
	}

	mSprite.scale(0.4f, 0.4f);

	//Set camera position
	sf::Vector2f camPos = mPosition - display.getCamera().getPosition();
	display.getCamera().move(sf::Vector2f(camPos.x*0.05, camPos.y*0.05));
	

	//Set camera rotation
	float camRot = mSprite.getRotation() - display.getCamera().getRotation();
	
	while(camRot < -180) camRot += 360;
	while(camRot > 180) camRot -= 360;

	if(mCanJump)
		display.getCamera().rotate(camRot*0.01);
	else
		display.getCamera().rotate(camRot*0.03);

	display.render(mSprite);
	mYarn.render(display);

}

void Cat::onCollision(std::shared_ptr<Entity> entity)
{
	std::shared_ptr<Ball> ball = std::dynamic_pointer_cast<Ball>(entity);
	std::shared_ptr<LooseEnd> loose = std::dynamic_pointer_cast<LooseEnd>(entity);

	if (ball)
	{
		mStandsOn.push_back(ball);

		sf::Vector2f dVec = mPosition - ball->getPosition();
		dVec = Util::normalize(dVec);
		float distance = ball->getRadius() + mRadius;
		dVec = dVec * distance;
		mPosition = ball->getPosition() + dVec;
		mGravityAcc = sf::Vector2f(0, 0);

		if(mCanJump && mAnimations.getCurrentAnimation() == "inair")
		{
			mAnimations.setCurrentAnimation("land");	
		}
		if(mAnimations.getCurrentAnimation() != "jump")
		{
			mCanJump = true;
		}
	}
	if (loose)
	{
		if(mNextYarn == loose->getIndexValue())
		{
			if (loose->getIndexValue() >= mThreadTextures.size())
				mYarn.setTexture(&mThreadTextures.back());
			else
				mYarn.setTexture(&mThreadTextures[loose->getIndexValue()]);

			loose->kill();

			mNextYarn++;
		}

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

int Cat::getNextYarn()const
{
	return mNextYarn;
}