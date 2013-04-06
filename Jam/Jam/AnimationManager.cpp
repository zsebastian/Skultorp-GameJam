#include "AnimationManager.h"
#include "tinyxml2.h"
#include "Utility.h"

AnimationManager::AnimationManager(std::string texture):
	mSize(256),
	mCurrentAnimation("idle"),
	mElapsed(0.f),
	mUpdateRate(100.f),
	mCurrentFrame(0)
{
	mTextureBox = sf::IntRect(0, 0, mSize, mSize),

	mFrameClock.restart();

	mTexture.loadFromFile(texture);
	mSprite.setTexture(mTexture);
	mSprite.setTextureRect(mTextureBox);
	mSprite.setOrigin(mSprite.getLocalBounds().width / 2, mSprite.getLocalBounds().height / 2);
	
	init();
}


AnimationManager::~AnimationManager()
{
}

void AnimationManager::setCurrentAnimation(std::string animation)
{
	mCurrentAnimation = animation;
	mCurrentFrame = 0;
}

sf::Sprite AnimationManager::getSprite(sf::Vector2f& position)
{
	for(mElapsed += mFrameClock.restart().asMilliseconds(); mElapsed > mUpdateRate; mElapsed -= mUpdateRate)
	{
		mCurrentFrame++;
		if(mCurrentFrame >= mAnimations[mCurrentAnimation].mNumberOfFrames)
		{
			mCurrentFrame = 0;
			if(!mAnimations[mCurrentAnimation].mLooping)
			{
				mCurrentAnimation = mAnimations[mCurrentAnimation].mNext;
			}
		}
	}

	mSprite.setPosition(position);
	setTextBox();

	return mSprite;
}

void AnimationManager::setTextBox()
{
	mTextureBox.left = mCurrentFrame * mSize;
	mTextureBox.top = mAnimations[mCurrentAnimation].mRowOfSprite * mSize;
	mSprite.setTextureRect(mTextureBox);
}

void AnimationManager::init()
{
	tinyxml2::XMLDocument doc;
	doc.LoadFile("animations.xml");

	tinyxml2::XMLElement* root = doc.FirstChildElement("Body");
	root = root->FirstChildElement("Animation");

	while(root)
	{
		std::string name = root->Attribute("name");
		int rowOfSprite = Util::fromString<int>(root->Attribute("rowOfSprite"));
		int numberOfFrames = Util::fromString<int>(root->Attribute("numberOfFrames"));
		bool looping = Util::fromString<bool>(root->Attribute("looping"));
		std::string next = root->Attribute("next");

		mAnimations.insert(std::make_pair(name, Animation(rowOfSprite, numberOfFrames, looping, next)));

		root = root->NextSiblingElement();
	}
}

void AnimationManager::setRotation(float angle)
{
	mSprite.rotate(angle);
	if(mSprite.getRotation() >= 359)
	{
		mSprite.setRotation(0);
	}
}