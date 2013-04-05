#include <SFML/Graphics.hpp>
#include "Display.h"

int main()
{
	Display display(sf::VideoMode(200, 200), "SFML works!");

    while (display.isOpen())
    {
		display.pollEvents();
		display.clear();

        display.flip();
    }

    return 0;
}