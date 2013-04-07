/*	The GUIBox acts as a parent and a container for other GUIWidgets.
 *	All GUIWidgets are rendered and their events handled relative to the
 *	position of its parent box (if any).
 *		Written: Sebastian Zander 13-02-04 11:49
 */
#ifndef GUIBOX_H
#define GUIBOX_H

#include "GUIWidget.h"
#include <SFML\Graphics\Rect.hpp>
#include <vector>
#include <SFML\Graphics\Sprite.hpp>
class Display;

class GUIBox : public GUIWidget
{
public:
	typedef std::shared_ptr<GUIBox> Ptr;

	static Ptr create(sf::FloatRect boxRect);

	GUIBox(sf::FloatRect boxRect);

	bool handleEvent(sf::Event& ev, sf::Vector2f relativeTo = sf::Vector2f(0, 0));
	void render(Display& display, sf::Vector2f = sf::Vector2f(0, 0));

	void setVisible(bool visible = true);
	void addChild(GUIWidget::Ptr child);

	void setSprite(const sf::Sprite& sprite);
private:
	std::vector<GUIWidget::Ptr> mChildren;

	bool mVisible;
	sf::Sprite mSprite;
};

#endif
