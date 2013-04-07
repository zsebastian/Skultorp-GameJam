/*	A GUIButton is a GUIWidget which can be pressed.
 *		Written: Sebastian Zander 13-02-04 11:50
 */

#ifndef GUIBUTTON_H
#define GUIBUTTON_H

#include "GUIWidget.h"
#include <SFML\Graphics\Rect.hpp>
#include <SFML\Graphics\Sprite.hpp>

class Display;

class GUIButton : public GUIWidget
{

public:
	typedef std::shared_ptr<GUIButton> Ptr;
	static Ptr create(sf::FloatRect buttonRect, const sf::Sprite& sprite);
	GUIButton(sf::FloatRect buttonRect, const sf::Sprite& sprite);

	bool handleEvent(sf::Event& ev, sf::Vector2f relativeTo = sf::Vector2f(0, 0));
	void render(Display& display, sf::Vector2f = sf::Vector2f(0, 0));

	void setVisible(bool visible = true);

	void setOnMouseUpFunction(std::function<void (Ptr)>);


	void setOnMouseDownSprite(const sf::Sprite& sprite);
	void setOnMouseHoverSprite(const sf::Sprite& sprite);
	void setIdleSprite(const sf::Sprite& sprite);

private:


	Ptr getThis();
	std::function<void (Ptr)> mOnMouseUp;
	
	sf::Sprite mCurrentSprite;

	sf::Sprite mMouseDownSprite;
	sf::Sprite mMouseHoverSprite;
	sf::Sprite mIdleSprite;

	size_t mMouseClickFrame;
	bool mTimerActive;

	bool mButtonIsDown;
	bool mVisible;
};

#endif