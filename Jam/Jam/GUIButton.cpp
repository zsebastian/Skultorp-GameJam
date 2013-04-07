#include "GUIButton.h"
/*	This function makes it easier to create a GUIButton
 *		Written: Sebastian Zander: 13-02-04 13:12
 */
GUIButton::Ptr GUIButton::create(sf::FloatRect buttonRect, const sf::Sprite& sprite)
{
	return std::make_shared<GUIButton>(buttonRect, sprite);
}

/*	Constructor.
 *		Written: Sebastian Zander: 13-02-04 13:14
 */
GUIButton::GUIButton(sf::FloatRect buttonRect, const sf::Sprite& sprite)
	:mIdleSprite(sprite)
	,mMouseDownSprite(sprite)
	,mMouseHoverSprite(sprite)
	,GUIWidget(buttonRect)
	,mOnMouseUp([](GUIButton::Ptr){})
	,mCurrentSprite(sprite)
{
	mButtonIsDown = false;
	mTimerActive = false;
	mVisible = true;
}

/*	This handles an event for the button.
 *	It will check if the button was pressed. It will change
 *	the sprite accordingly.
 *		Written: Sebastian Zander: 13-02-04 13:16
 */
bool GUIButton::handleEvent(sf::Event& ev, sf::Vector2f relativeTo)
{
	if (mVisible)
	{
		if (ev.type == sf::Event::MouseButtonPressed)
		{
			if (ev.mouseButton.button == sf::Mouse::Button::Left)
			{
				sf::FloatRect buttonRect = Rect();
				buttonRect.left += relativeTo.x;
				buttonRect.top += relativeTo.y;
				if (buttonRect.contains(ev.mouseButton.x, ev.mouseButton.y))
				{
					mCurrentSprite = mMouseDownSprite;
					mButtonIsDown = true;
					return true;
				}
			}
		}
		
		else if (ev.type == sf::Event::MouseButtonReleased)
		{
			if (ev.mouseButton.button == sf::Mouse::Button::Left && mButtonIsDown)
			{
				sf::FloatRect buttonRect = Rect();
				buttonRect.left += relativeTo.x;
				buttonRect.top += relativeTo.y;
				if (buttonRect.contains(ev.mouseButton.x, ev.mouseButton.y))
				{
					mCurrentSprite = mMouseHoverSprite;
					mMouseClickFrame = 0;
					mTimerActive = true;
					mButtonIsDown = false;
					mOnMouseUp(getThis());

					return true;
				}

			}
		}
		
		else if (ev.type == sf::Event::MouseMoved)
		{
			sf::FloatRect buttonRect = Rect();
			buttonRect.left += relativeTo.x;
			buttonRect.top += relativeTo.y;
			if ((!mButtonIsDown && !mTimerActive && buttonRect.contains(ev.mouseMove.x, ev.mouseMove.y)))
			{
				mCurrentSprite = mMouseHoverSprite;
			}
			else
			{
				mCurrentSprite = mIdleSprite;
			}
		}
	}

	return false;
}

/*	This returns a safe shared pointer from this.
 *		Written: Sebastian Zander: 13-02-04 13:16
 */
GUIButton::Ptr GUIButton::getThis()
{
	return std::dynamic_pointer_cast<GUIButton>(shared_from_this());
}

/*	This renders the correct button srite
 *		Written: Sebastian Zander: 13-02-04 13:23
 */
void GUIButton::render(Display& display, sf::Vector2f relativeTo)
{
	if (mVisible)
	{
		mCurrentSprite.setPosition(relativeTo.x + Rect().left, relativeTo.y + Rect().top);
		display.render(mCurrentSprite);
	}
	if (mTimerActive)
	{
		//this is used to time the button-down sprite, so it doesn't show for too short a time.
		mMouseClickFrame++;
	
		if (!mButtonIsDown && mMouseClickFrame > 10)
		{
			mCurrentSprite = mIdleSprite;
			mTimerActive = false;
		}
	}

}

/*	This sets the button to visible.
 *		Written: Sebastian Zander: 13-02-04 13:27
 */
void GUIButton::setVisible(bool visible)
{
	mVisible = visible;
}

/*	This sets the function to be called on a mouse-up event on the button
 *		Written: Sebastian Zander: 13-02-04 13:26
 */
void GUIButton::setOnMouseUpFunction(std::function<void (GUIButton::Ptr)> func)
{
	mOnMouseUp = func;
}

/*	This sets the sprite to be displayed on a mouse-down event
 *		Written: Sebastian Zander: 13-02-04 13:26
 */
void GUIButton::setOnMouseDownSprite(const sf::Sprite& sprite)
{
	mMouseDownSprite = sprite;
}

/*	This sets the sprite to be displayed on a mouse-hover event
 *		Written: Sebastian Zander: 13-02-04 13:26
 */
void GUIButton::setOnMouseHoverSprite(const sf::Sprite& sprite)
{
	mMouseHoverSprite = sprite;
}

/*	This sets the sprite to be displayed on idle
 *		Written: Sebastian Zander: 13-02-04 13:26
 */
void GUIButton::setIdleSprite(const sf::Sprite& sprite)
{
	mIdleSprite = sprite;
}