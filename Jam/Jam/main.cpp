#include <SFML/Graphics.hpp>
#include "Display.h"
#include "StateManager.h"
#include "Game.h"

int main()
{

	Display display(sf::VideoMode(800, 600), "YarnCat");
	StateManager stateManager;

	stateManager.pushState(std::make_shared<Game>());

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