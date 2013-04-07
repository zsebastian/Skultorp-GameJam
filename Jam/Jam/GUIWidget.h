/*	This is the abstract baseclass for widgets
 *	handleEvent is supposed to return false
 *	if the event was not handled, true otherwise
 *		Written: Sebastian Zander 2013-01-28 19:26
 */

#ifndef GUIWIDGET_H
#define GUIWIDGET_H

#include <SFML\Window\Event.hpp>
#include <memory>
#include <functional>
#include <SFML\Graphics\Rect.hpp>
#include "Display.h"

class GUIWidget: public std::enable_shared_from_this<GUIWidget>
{
public:
	typedef std::shared_ptr<GUIWidget> Ptr;

	virtual ~GUIWidget() {};
	GUIWidget(const sf::FloatRect& rect): mRect(rect) {};

	virtual bool handleEvent(sf::Event& ev, sf::Vector2f relativeTo = sf::Vector2f(0, 0)) = 0;
	virtual void render(Display& display, sf::Vector2f = sf::Vector2f(0, 0)) = 0;

	const sf::FloatRect& Rect() const {return mRect;}; 
	sf::FloatRect& Rect() {return mRect;}; 

private:
	sf::FloatRect mRect;
};
	
#endif