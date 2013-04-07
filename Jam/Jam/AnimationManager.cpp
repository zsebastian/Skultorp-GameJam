#include "AnimationManager.h"
#include "tinyxml2.h"
#include "Utility.h"
#include <regex>
#include <utility>

AnimationManager::AnimationManager(std::string texture):
	mSize(256),
	mCurrentAnimation("idle"),
	mElapsed(0.f),
	mUpdateRate(150.f),
	mCurrentFrame(0)
{
	std::string t0 = regexReplace("$rand(1,2) och $rand(1,3)");
	std::string t1 = regexReplace("$rand(4,6) och $rand(2,6)");
	std::string t2 = regexReplace("test$rand(2,6)");
	std::string t3 = regexReplace("anim$rand(1,20)+$rand(-10,20)");

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
	if(animation != mCurrentAnimation)
	{
		mCurrentAnimation = regexReplace(animation);
		mCurrentFrame = 0;
		mCurrentAnimation = animation;
		mUpdateRate = mAnimations[mCurrentAnimation].mUpdateRate;
	}

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
				setCurrentAnimation(mAnimations[mCurrentAnimation].mNext);
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
	if (!root)
		return;

	root = root->FirstChildElement("Animation");

	while(root)
	{
		std::string name		= root->Attribute("name");
		int rowOfSprite			= Util::fromString<int>(root->Attribute("rowOfSprite"));
		int numberOfFrames		= Util::fromString<int>(root->Attribute("numberOfFrames"));
		bool looping			= Util::fromString<bool>(root->Attribute("looping"));
		std::string next		= root->Attribute("next");
		float updateRate		= Util::fromString<float>(root->Attribute("updateRate"));

		mAnimations.insert(std::make_pair(name, Animation(rowOfSprite, numberOfFrames, looping, next, updateRate)));

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

std::string AnimationManager::getCurrentAnimation()const
{
	return mCurrentAnimation;
}

std::string AnimationManager::regexReplace(const std::string& str)
{
	//"$rand(i0,i1)"
	//Doesn't work very well for negative numbers (when replacing them)
	std::smatch sm;	
	std::regex randExpr("\\$(rand)\\(\\s*(-?\\d+)\\s*,\\s*(-?\\d+)\\s*\\)");
	std::string ret = str;

	if (std::regex_search (str, sm , randExpr))
	{
		std::string key;
		std::string value;

		size_t i = 0 ;
		const std::sregex_iterator End;
		
		std::vector<std::pair<size_t, size_t>> iters;
		std::vector<std::string> replaces;

		for (std::sregex_iterator i(ret.begin(), ret.end(), randExpr); i != End; ++i)
		{
			if ((*i)[1].str() == "rand")
			{
				int i0 = Util::fromString<int>((*i)[2]);
				int i1 = Util::fromString<int>((*i)[3]);
				int value = Util::random(i0, i1);
				std::string replace(Util::toString(value));
				iters.push_back(std::make_pair((*i)[0].first - ret.begin(), (*i)[0].second - ret.begin()));
				replaces.push_back(replace);
			}
		}

		for (size_t j = 0; j < iters.size(); ++j)
		{
			ret.replace(ret.begin() + iters[j].first, ret.begin() + iters[j].second, replaces[j]);
			for (size_t corr = j + 1; corr < iters.size(); ++corr)
			{
				size_t dist = iters[i].second - iters[i].first - 1;
				iters[corr].first -= dist;
				iters[corr].second -= dist;
			}
		}
	}

	return ret;

}