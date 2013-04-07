#include "Ball.h"
#include "Display.h"
#include "Utility.h"
#include "TextureManager.h"
#include <algorithm>

Ball::Ball(const sf::Vector2f& position, float mass, float radius, size_t indexValue)
	:mMass(mass)
	,mActualMass(mass)
	,mPosition(position)
	,mIndexValue(indexValue)
{
	float originAdjustX = 0.f;
	float originAdjustY = 0.f;

	std::string textureFilename;
	switch(indexValue)
	{
	case 0:
		textureFilename = "data/yarn_ball_red.png";
		mScaleModifier = 2.2f;
		break;
	case 1:
		textureFilename = "data/yarn_ball_blue.png";
		mScaleModifier = 2.2f;
		break;
	case 2:
		textureFilename = "data/yarn_ball_yellow.png";
		originAdjustX = -16.5f;
		originAdjustY = -16.5f;
		mScaleModifier = 3.05f;

		break;
	case 3:
		textureFilename = "data/yarn_ball_green.png";
		mScaleModifier = 2.4f;
		break;
	case 4:
		textureFilename = "data/yarn_ball_goal.png";
		mScaleModifier = 7.f;
		originAdjustX = -27.f;
		originAdjustY = 27.f;

		break;
	default:
		textureFilename = "data/yarn_ball_red.png";
		mScaleModifier = 2.2f;
	}
	mSprite.setTexture(TextureManager::getTexture(textureFilename));
	float scale = (radius * mScaleModifier)/mSprite.getLocalBounds().width;

	sf::FloatRect localBounds = mSprite.getLocalBounds();
	mSprite.setOrigin(localBounds.width/2.f + originAdjustX * scale, localBounds.height/2.f + originAdjustY * scale);

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
	float scale = (radius * mScaleModifier)/mSprite.getLocalBounds().width;
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
	sf::FloatRect bounds = mSprite.getGlobalBounds();
	bounds.width /= 1.5f;
	bounds.height /= 1.5f;
	return bounds;
}

void Ball::resetMass()
{
	mActualMass = 1.f;
}

size_t Ball::getIndexValue() const
{
	return mIndexValue;
}

void Ball::setIndexValue(size_t indexValue)
{
	mIndexValue = indexValue;
}