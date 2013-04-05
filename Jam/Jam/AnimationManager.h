#ifndef INCLUDED_ANIMATION
#define INCLUDED_ANIMATION

#include <SFML/Graphics.hpp>

class Display;
class Animation
{
public:
	Animation(	int rowOfSprite, 
				int numberOfFrames,
				bool looping);
	~Animation();
	void update();
	void render(Display& display);

	bool getEndOfAnimation()const;

private:
	int mRowOfSprite;
	int mNumberOfFrames;
	bool mLooping;
	bool mEndOfAnimation;

	sf::Texture mTexture;
	sf::Sprite mSprite;
};

#endif