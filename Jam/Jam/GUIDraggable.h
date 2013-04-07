/*	A GUIDraggable is a widget which the user can drag around 
 *	with his mouse. It does not move itself though, but must be
 *	told to by the client (which recieves the positions of every
 *	mouse drag
 *		Written: Sebastian Zander 13-02-04 11:51
 */

#ifndef GUIDRAGGABLE_H
#define GUIDRAGGABLE_H

#include "GUIWidget.h"
#include <SFML\Graphics\Rect.hpp>
#include <SFML\Graphics\Sprite.hpp>
class Display;

class GUIDraggable : public GUIWidget
{
public:
	typedef std::shared_ptr<GUIDraggable> Ptr;
	static Ptr create(sf::FloatRect rect, const sf::Sprite& sprite);

	GUIDraggable(sf::FloatRect draggableRect, const sf::Sprite& sprite);

	bool handleEvent(sf::Event& ev, sf::Vector2f relativeTo = sf::Vector2f(0, 0));
	void render(Display& display, sf::Vector2f = sf::Vector2f(0, 0));

	void setVisible(bool visible = true);

	void setOnMouseUpFunction(std::function<void (Ptr, sf::Vector2f)>);
	void setOnMouseDownFunction(std::function<void (Ptr, sf::Vector2f)>);
	void setOnDragFunction(std::function<void (Ptr, sf::Vector2f from, sf::Vector2f to)>);

	void addChild(GUIWidget::Ptr child);

	sf::Sprite& getSprite() {return mSprite;};
	const sf::Sprite& getSprite() const {return mSprite;};

private:
	std::vector<GUIWidget::Ptr> mChildren;

	GUIDraggable::Ptr getThis();

	std::function<void (Ptr, sf::Vector2f)> mOnMouseUp;
	std::function<void (Ptr, sf::Vector2f)> mOnMouseDown;
	std::function<void (Ptr, sf::Vector2f from, sf::Vector2f to)> mOnDrag;

	sf::Sprite mSprite;

	bool mVisible;

	bool mIsActive;
	sf::Vector2f mDragFrom;
};

#endif