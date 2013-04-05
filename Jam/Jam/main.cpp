#include <SFML/Graphics.hpp>
#include "Display.h"
#include "StateManager.h"

int main()
{
	Display display(sf::VideoMode(800, 600), "YarnCat");
	StateManager stateManager;

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