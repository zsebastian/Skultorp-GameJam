#include "Display.h"
#include "EventManager.h"

Display::Display(sf::VideoMode videoMode, const std::string& windowText)
	:mWindow(videoMode, windowText)
	,EventHandler(sf::Event::Closed, [&](sf::Event ev){mWindow.close();})
{
	mWindow.setFramerateLimit(60);
}

void Display::render(const sf::Drawable& drawable)
{
	mWindow.draw(drawable);
}
	
void Display::flip()
{
	mWindow.display();
}

void Display::clear(sf::Color clearColor)
{
	mWindow.clear(clearColor);
}

void Display::pollEvents()
{
	sf::Event ev;
    while (mWindow.pollEvent(ev))
    {
		EventManager::getInstance()->newEvent(ev);
    }
}

bool Display::isOpen() const
{
	return mWindow.isOpen();
}
