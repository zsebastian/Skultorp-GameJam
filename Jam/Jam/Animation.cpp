#include "Animation.h"



Animation::Animation(	int rowOfSprite, 
						int numberOfFrames,
						bool looping):
	mRowOfSprite(rowOfSprite),
	mNumberOfFrames(numberOfFrames),
	mLooping(looping),
	mEndOfAnimation(false)
{


}


Animation::~Animation()
{
}
