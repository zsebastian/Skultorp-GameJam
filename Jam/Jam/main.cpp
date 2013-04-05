#include <SFML/Graphics.hpp>
#include "Display.h"
#include "StateManager.h"

int main()
{
<<<<<<< HEAD
	Display display(sf::VideoMode(800, 600), "YarnCat");
	StateManager stateManager;
=======
	Display display(sf::VideoMode(1024, 768), "SFML works!");
>>>>>>> 21bf75a87a1a5c34c0cbe6e2c3ca17d426a05ce8

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