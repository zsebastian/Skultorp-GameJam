#include "GUIDraggable.h"


#include <iostream>

GUIDraggable::Ptr GUIDraggable::create(sf::FloatRect rect, const sf::Sprite& sprite)
{
	return std::make_shared<GUIDraggable>(rect, sprite);
}

GUIDraggable::GUIDraggable(sf::FloatRect draggableRect, const sf::Sprite& sprite)
	:GUIWidget(draggableRect)
	,mOnMouseDown([](GUIDraggable::Ptr, sf::Vector2f){})
	,mOnDrag([](GUIDraggable::Ptr, sf::Vector2f, sf::Vector2f){})
	,mOnMouseUp([](GUIDraggable::Ptr, sf::Vector2f){})
	,mSprite(sprite)
	,mIsActive(false)
	,mVisible(true)
{

}


void GUIDraggable::setOnDragFunction(std::function<void (Ptr, sf::Vector2f from, sf::Vector2f to)> onDrag)
{
	mOnDrag = onDrag;
}

void GUIDraggable::setOnMouseUpFunction(std::function<void (Ptr, sf::Vector2f)> onMouseUp)
{
	mOnMouseUp = onMouseUp;
}

void GUIDraggable::setOnMouseDownFunction(std::function<void (Ptr, sf::Vector2f)> onMouseDown)
{
	mOnMouseDown = onMouseDown;
}

bool GUIDraggable::handleEvent(sf::Event& ev, sf::Vector2f relativeTo)
{

	if (ev.type == sf::Event::MouseButtonReleased)
	{
		sf::FloatRect buttonRect = Rect();
				buttonRect.left += relativeTo.x;
				buttonRect.top += relativeTo.y;

		if (mIsActive)
		{
			mOnMouseUp(getThis(), sf::Vector2f(ev.mouseButton.x - buttonRect.left, ev.mouseButton.y - buttonRect.top));
		
			mIsActive = false;
		}
	}


	if (mVisible)
	{

		for (auto iter = mChildren.begin(); iter != mChildren.end(); ++iter)
		{
			if ((*iter)->handleEvent(ev, sf::Vector2f(Rect().left + relativeTo.x, Rect().top + relativeTo.y)) == true)
				return true;
		}


		if (ev.type == sf::Event::MouseButtonPressed)
		{
		
			if (ev.mouseButton.button == sf::Mouse::Button::Left)
			{
				sf::FloatRect buttonRect = Rect();
				buttonRect.left += relativeTo.x;
				buttonRect.top += relativeTo.y;
				

				if (buttonRect.contains(ev.mouseButton.x, ev.mouseButton.y))
				{
					mIsActive = true;
					mOnMouseDown(getThis(), sf::Vector2f(ev.mouseButton.x - buttonRect.left, ev.mouseButton.y - buttonRect.top));
					
					return true;
				}
			}
		}

		if (ev.type == sf::Event::MouseButtonReleased)
		{
			sf::FloatRect buttonRect = Rect();
			buttonRect.left += relativeTo.x;
			buttonRect.top += relativeTo.y;
	
			mIsActive = false;

			if (buttonRect.contains(ev.mouseButton.x, ev.mouseButton.y))
			{
				mOnMouseUp(getThis(), sf::Vector2f(ev.mouseButton.x - buttonRect.left, ev.mouseButton.y - buttonRect.top));
				return true;
			}
		}

		else if (ev.type == sf::Event::MouseMoved)
		{
			sf::Vector2f oldV(Rect().left, Rect().top);

			if (mIsActive)
			{
				mOnDrag(getThis(), mDragFrom, sf::Vector2f(ev.mouseMove.x - relativeTo.x - Rect().left, ev.mouseMove.y - relativeTo.y - Rect().top));
			}

			sf::Vector2f newV(Rect().left, Rect().top);
			
			sf::Vector2f move = newV - oldV;

			mDragFrom.x = ev.mouseMove.x - relativeTo.x - Rect().left;// - move.x;
			mDragFrom.y = ev.mouseMove.y - relativeTo.y - Rect().top;// - move.y;
		}
	}
	else
	{
		mIsActive = false;
	}
	return false;
}

void GUIDraggable::render(Display& display, sf::Vector2f relativeTo)
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

GUIDraggable::Ptr GUIDraggable::getThis()
{
	return std::dynamic_pointer_cast<GUIDraggable>(shared_from_this());
}

void GUIDraggable::setVisible(bool visible)
{
	mVisible = visible;
	if (!mVisible)
		mIsActive = false;
}

void GUIDraggable::addChild(GUIWidget::Ptr child)
{
	mChildren.push_back(child);
}