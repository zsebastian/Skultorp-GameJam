#include "LooseEnd.h"
#include "Display.h"
#include "Cat.h"
#include "Ball.h"
#include "Utility.h"
#include "TextureManager.h"

LooseEnd::LooseEnd(std::shared_ptr<Ball> belongsTo, float positionAngle)
	:mBelongsTo(belongsTo)
	,mPositionAngle(positionAngle)
	,mIndexValue(belongsTo->getIndexValue())
{
	mSprite.setTexture(TextureManager::getTexture("data/looseend.png"));

	sf::Vector2f ballPos = mBelongsTo.lock()->getPosition();
	float distance =  mBelongsTo.lock()->getRadius();;
	sf::Vector2f placeVec(Util::getVectorFromAngle<float>(positionAngle) * distance);
	mPosition = ballPos + placeVec;
	mSprite.setRotation(positionAngle + 90);
	mSprite.setOrigin(mSprite.getTextureRect().width / 2, mSprite.getTextureRect().height / 2);
	
	mRadius = mSprite.getTextureRect().height / 2;
}

void LooseEnd::setPosition(const sf::Vector2f& position)
{
	if (mBelongsTo.expired())
		return;

	sf::Vector2f ballPos = mBelongsTo.lock()->getPosition();
	sf::Vector2f distVec =  position - ballPos;

	//if(!mBelongsTo.expired())
		float distance = mBelongsTo.lock()->getRadius();
	
	sf::Vector2f placeVec(Util::normalize(distVec) * distance);

	mPosition = placeVec + ballPos;
	mPositionAngle = Util::angle(mPosition - ballPos);

	mSprite.setRotation(mPositionAngle + 90);
}

void LooseEnd::setMass(float mass)
{
	mMass = mass;
}

void LooseEnd::setRadius(float radius)
{
	mRadius = radius;
}

void LooseEnd::update()
{
	if (mBelongsTo.expired())
		kill();

	updatePosition();
}

void LooseEnd::render(Display& display)
{
	mSprite.setPosition(mPosition);

	display.render(mSprite);
}

void LooseEnd::onCollision(std::shared_ptr<Entity> entity)
{
	std::shared_ptr<Cat> cat = std::dynamic_pointer_cast<Cat>(entity);

	if (cat)
	{

	}
}

sf::Vector2f LooseEnd::getPosition() const
{
	return mPosition;
}

float LooseEnd::getMass() const
{
	return mMass;
}

float LooseEnd::getRadius() const
{
	return mRadius;
}

sf::FloatRect LooseEnd::getGlobalBounds() const
{
	return mSprite.getGlobalBounds();
}

size_t LooseEnd::getIndexValue() const
{
	return mIndexValue;
}

void LooseEnd::updatePosition()
{
	if (mBelongsTo.expired())
		return;

	sf::Vector2f ballPos = mBelongsTo.lock()->getPosition();
	float distance =  mBelongsTo.lock()->getRadius();;
	sf::Vector2f placeVec(Util::getVectorFromAngle<float>(mPositionAngle) * distance);
	mPosition = ballPos + placeVec;

}