#include <SFML/Graphics.hpp>
#include "Display.h"
#include "StateManager.h"
<<<<<<< HEAD
#include "Utility.h"
=======
#include "Game.h"
>>>>>>> 5a632a71645147d3fa6577815451299287602d92

int main()
{

	int i = Util::fromString<int>("1");
	std::string str = Util::toString(12);

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