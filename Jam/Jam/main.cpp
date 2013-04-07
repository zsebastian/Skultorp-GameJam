#include <SFML/Window/VideoMode.hpp>
#include "Display.h"
#include "StateManager.h"
#include "MainMenu.h"

int main()
{
	Display display(sf::VideoMode(1280, 720), "YarnCat");
	StateManager stateManager;

	stateManager.pushState(std::make_shared<MainMenu>(stateManager));

    while (display.isOpen())
    {
		display.pollEvents();
		stateManager.update();

		display.clear();
		stateManager.render(display);
        display.flip();
    }

    return 0;
}