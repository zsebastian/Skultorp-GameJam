#ifndef DISPLAY_H
#define DISPLAY_H

#include <SFML/Graphics.hpp>
#include <string>
#include "EventHandler.h"
#include "Camera.h"

class Display : public EventHandler
{
public:
	Display(sf::VideoMode videoMode, const std::string& windowText);
	void render(const sf::Drawable& drawable);
	void render(const sf::Drawable& drawable, const sf::RenderStates& renderState);
	
	void flip();
	void clear(sf::Color clearColor = sf::Color::Black);

	void pollEvents();

	bool isOpen() const;
	sf::RenderWindow& getWindow();
	Camera& getCamera();
	void setToDefaultView();
private:
	sf::RenderWindow mWindow;
	Camera mCamera;
};

#endif