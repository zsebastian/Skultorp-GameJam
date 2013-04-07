#include "GUIBox.h"

/*	This function can be used to make it simpler to create a GUIBox
 *		Written: Sebastian Zander 13-02-04 13:07
 */
GUIBox::Ptr GUIBox::create(sf::FloatRect boxRect)
{
	return std::make_shared<GUIBox>(boxRect);
}

/*	Constructor
 *		Written: Sebastian Zander 13-02-04 13:08
 */
GUIBox::GUIBox(sf::FloatRect boxRect)
	:GUIWidget(boxRect)
{
	mVisible = true;
}

/*	This calls handle event, if visible, for all the children until one of the children return true.
 *	It returns true if an event was handled. It calls handleEvent on its children relative to its
 *	own position.
 *		Written: Sebastian Zander 13:09 13-02-04
 */
bool GUIBox::handleEvent(sf::Event& ev, sf::Vector2f relativeTo)
{
	bool eventHandled = false;

	if (mVisible)
	{
		for (auto iter = mChildren.begin(); iter != mChildren.end(); ++iter)
		{
			if ((*iter)->handleEvent(ev, sf::Vector2f(Rect().left + relativeTo.x, Rect().top + relativeTo.y)) == true)
				return true;
		}
	}
		//handle events

	return eventHandled;
}

/*	This renders children and itself to the canvas, if visible.
 *	It will render itself on canvasLayer on the canvas, while rendering
 *	its children on canvasLayer + 1. It renders its children relative to its
 *  own position
 *		Written: Sebastian Zander: 13-02-04 13:09
 */
void GUIBox::render(Display& display, sf::Vector2f relativeTo)
{
	if (mVisible)
	{
		for (auto iter = mChildren.begin(); iter != mChildren.end(); ++iter)
		{
			(*iter)->render(display, sf::Vector2f(Rect().left + relativeTo.x, Rect().top + relativeTo.y));
		}

		mSprite.setPosition(relativeTo.x + Rect().left, relativeTo.y + Rect().top);

		display.render(mSprite);
	}

}

/*	This sets the GUIBox to visible
 *		Written: Sebastian Zander: 13-02-04 13:10
 */
void GUIBox::setVisible(bool visible)
{
	mVisible = visible;
}

/*	This adds a child to the box.
 *		Written: Sebastian Zander: 13-02-04 13:10
 */
void GUIBox::addChild(GUIWidget::Ptr child)
{
	mChildren.push_back(child);
}

/*	This sets a sprite for the GUIBox
 *		Written
 */
void GUIBox::setSprite(const sf::Sprite& sprite)
{
	mSprite = sprite;
}