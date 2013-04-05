#include "AnimationManager.h"
#include "tinyxml2.h"

AnimationManager::AnimationManager(std::string texture):
	mCurrentAnimation("idle"),
	mTextureBox(0, 0, 512, 512),
	mElapsed(0.f),
	mUpdateRate(200.f),
	mCurrentFrame(0)
{
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

sf::Sprite AnimationManager::getSprite()
{
	for(mElapsed += mFrameClock.restart().asMilliseconds(); mElapsed > mUpdateRate; mElapsed -= mUpdateRate)
	{
		mCurrentFrame++;
		if(mCurrentFrame > mAnimations[mCurrentAnimation].mNumberOfFrames)
		{
			mCurrentFrame = 0;
			if(!mAnimations[mCurrentAnimation].mLooping)
			{
				mCurrentAnimation = mAnimations[mCurrentAnimation].mNext;
			}
		}
	}

	setTextBox();

	return mSprite;
}

void AnimationManager::setTextBox()
{
	mTextureBox.left = mCurrentFrame * 512;
	mTextureBox.top = mAnimations[mCurrentAnimation].mRowOfSprite * 512;
}

void AnimationManager::init()
{
	tinyxml2::XMLDocument doc;
	doc.LoadFile("animations.xml");

	tinyxml2::XMLElement* root = doc.FirstChildElement("body");
	root = root->FirstChildElement("Animation");

	while(root)
	{
		int rowOfSprite = 0;
		int numberOfFrames = 0;
		bool looping = true;
		std::string next = "none";

		tinyxml2::XMLAttribute* atri = root->FirstAttribute;

		while(atri)
		{
			std::string value = atri->Name();
			if(value == "rowOfSprite")
			{
				//rowOfSprite = static_cast<int>(atri->Value());
			}
		}

		root = root->NextSiblingElement();
	}
}