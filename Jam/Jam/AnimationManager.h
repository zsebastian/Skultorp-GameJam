#ifndef INCLUDED_ANIMATION
#define INCLUDED_ANIMATION

#include <SFML/Graphics.hpp>
#include <map>
#include <string>

class Display;
class AnimationManager
{
public:
	AnimationManager(std::string texture);
	~AnimationManager();

	void setCurrentAnimation(std::string animation);
	void setRotation(float angle);
	
	sf::Sprite getSprite(sf::Vector2f& position);
	std::string getCurrentAnimation()const;

private:

	void init();
	std::string regexReplace(const std::string& str);

	// textures
	sf::Texture mTexture;
	sf::Sprite mSprite;

	// Animation
	std::string mCurrentAnimation;
	sf::IntRect mTextureBox;
	int mCurrentFrame;
	void setTextBox();
	int mSize;

	// clock
	sf::Clock mFrameClock;
	float mElapsed;
	float mUpdateRate;

	struct Animation
	{
		Animation(	int rowOfSprite = 0, 
					int numberOfFrames = 0,
					bool looping = true,
					std::string next = "none",
					float updateRate = 150.f)
		{
			mRowOfSprite = rowOfSprite;
			mNumberOfFrames = numberOfFrames;
			mLooping = looping;
			mNext = next;
			mUpdateRate = updateRate;
		}



		int mRowOfSprite;
		int mNumberOfFrames;
		bool mLooping;
		std::string mNext;
		float mUpdateRate;
	};

	std::map<std::string, Animation> mAnimations;

};

#endif