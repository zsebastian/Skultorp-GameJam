#ifndef MAINMENU_H
#define MAINMENU_H

#include "State.h"
#include "GUIBox.h"
#include "EventHandler.h"
#include <SFML\Graphics\Texture.hpp>
#include "GUIButton.h"

class MainMenu : public State
{
public:
	MainMenu(StateManager& stateManager);
		
	void render(Display&);
	void update();
	bool isAlive();

private:
	GUIBox::Ptr mGuiBox;

	void startGame(GUIButton::Ptr button);
	void startOptions(GUIButton::Ptr button);
	void exitGame(GUIButton::Ptr button);

	void handleEvents(sf::Event& ev);
	EventHandler eventHandler;

	sf::Texture mButtonTexture;

	bool mIsAlive;
};

#endif