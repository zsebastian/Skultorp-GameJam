#include "AnimationManager.h"
#include "tinyxml2.h"
#include "Utility.h"

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
	
	//init();
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
	mSprite.setPosition(position);

	return mSprite;
}

void AnimationManager::setTextBox()
{
	mTextureBox.left = mCurrentFrame * 512;
	mTextureBox.top = mAnimations[mCurrentAnimation].mRowOfSprite * 512;
}

void AnimationManager::init()
{

<<<<<<< HEAD
	tinyxml2::XMLElement* root = doc.FirstChildElement("body");
	root = root->FirstChildElement("Animation");

	while(root)
	{
		int rowOfSprite = Util::fromString<int>(root->Attribute("rowOfSprite"));
		int numberOfFrames = Util::fromString<int>(root->Attribute("numberOfFrames"));
		bool looping = Util::fromString<bool>(root->Attribute("looping"));
		std::string next = root->Attribute("next");

		std::string name = root->Attribute("name");

		mAnimations.insert(std::make_pair(name, Animation(rowOfSprite, numberOfFrames, looping, next)));

		root = root->NextSiblingElement();
	}
}
=======
}
>>>>>>> d8e55607a4f61cb6df548f2e43a37c96ce000613
