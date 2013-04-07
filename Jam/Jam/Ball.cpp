#include "Ball.h"
#include "Display.h"
#include "Utility.h"

Ball::Ball(const sf::Vector2f& position, float mass, float radius, int index)
	:mMass(mass)
	,mActualMass(mass)
	,mPosition(position)
	,mIndex(index)
{
	switch(index)
	{
	case 0:
		mTexture.loadFromFile("data/yarn_ball.png");
		break;
	case 1:
		mTexture.loadFromFile("data/yarn_ball_large.png");
		break;
	case 2:
		mTexture.loadFromFile("data/yarn_ball_small.png");
		break;
	case 3:
		mTexture.loadFromFile("data/yarn_ball_large.png");
		break;
	case 4:
		mTexture.loadFromFile("data/yarn_ball.png");
		break;
	case 5:
		mTexture.loadFromFile("data/yarn_ball_small.png");
		break;
	}

	mSprite.setTexture(mTexture);

	sf::FloatRect localBounds = mSprite.getLocalBounds();
	mSprite.setOrigin(localBounds.width/2.f, localBounds.height/2.f);

	setRadius(radius);
}

Ball::~Ball()
{
	
}

void Ball::setPosition(const sf::Vector2f& position)
{
	mPosition = position;
}

void Ball::setMass(float mass)
{
	mMass = mass;
}

void Ball::setRadius(float radius)
{
	mRadius = radius;
	float scale = (radius*2.2f)/mSprite.getLocalBounds().width;
	mSprite.setScale(scale, scale);
}

void Ball::update()
{
	//HOOOOOOOOW
	mActualMass += mMass / 500.f;

	if (mActualMass > mMass)
		mActualMass = mMass;

	mSprite.setPosition(mPosition);
}

void Ball::render(Display& display)
{
	display.render(mSprite);
}

void Ball::onCollision(std::shared_ptr<Entity> entityy)
{

}

sf::Vector2f Ball::getPosition() const
{
	return mPosition;
}

float Ball::getMass() const
{
	return mActualMass;
}

float Ball::getRadius() const
{
	return mRadius;
}

sf::FloatRect Ball::getGlobalBounds() const
{
	return mSprite.getGlobalBounds();
}

int Ball::getIndex() const
{
	return mIndex;
}

void Ball::resetMass()
{
	mActualMass = 1.f;
}