#include "Display.h"
#include "EventManager.h"

Display::Display(sf::VideoMode videoMode, const std::string& windowText)
	:mWindow(videoMode, windowText)
	,mCamera(sf::Vector2f(videoMode.width, videoMode.height), sf::Vector2f())
	,EventHandler(sf::Event::Closed, [&](sf::Event ev){mWindow.close();})
{
	mWindow.setFramerateLimit(60);
	mWindow.setVerticalSyncEnabled(true);
}

void Display::render(const sf::Drawable& drawable)
{
	mWindow.setView(mCamera.getView());
	mWindow.draw(drawable);
}

void Display::render(const sf::Drawable& drawable, const sf::RenderStates& renderState)
{
	mWindow.setView(mCamera.getView());
	mWindow.draw(drawable, renderState);
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

sf::RenderWindow& Display::getWindow()
{
	return mWindow;
}

Camera& Display::getCamera()
{
	return mCamera;
}

void Display::setToDefaultView()
{
	mCamera.getView() = mWindow.getDefaultView(); 
}
