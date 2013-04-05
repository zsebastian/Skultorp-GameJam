#include <SFML/Graphics.hpp>
#include "Display.h"
#include "StateManager.h"
#include "Utility.h"

int main()
{

	int i = Util::fromString<int>("1");
	std::string str = Util::toString(12);

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