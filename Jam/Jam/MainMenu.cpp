#include "MainMenu.h"
#include "StateManager.h"
#include <memory>
#include "Game.h"

MainMenu::MainMenu(StateManager& stateManager)
	:State(stateManager)
	,mGuiBox(GUIBox::create(sf::FloatRect(0.f, 0.f, 800.f, 600.f)))
{
	mButtonTexture.loadFromFile("data/menubuttons.png");

	GUIButton::Ptr start = GUIButton::create(sf::FloatRect(10.f, 10.f, 512.f, 256.f), sf::Sprite(mButtonTexture, sf::IntRect(0, 0, 512, 256)));
	start->setOnMouseHoverSprite(sf::Sprite(mButtonTexture, sf::IntRect(512, 0, 512, 256)));
	start->setOnMouseDownSprite(sf::Sprite(mButtonTexture, sf::IntRect(1028, 0, 512, 256)));

	start->setOnMouseUpFunction(std::bind(&MainMenu::startGame, this, std::placeholders::_1));
	mGuiBox->addChild(start);
	
	std::function<void (sf::Event&)> handler = std::bind(&MainMenu::handleEvents, this, std::placeholders::_1);

	eventHandler.addEventListener(sf::Event::MouseButtonPressed, handler);
	eventHandler.addEventListener(sf::Event::MouseButtonReleased, handler);
	eventHandler.addEventListener(sf::Event::MouseMoved, handler);

}

void MainMenu::startGame(GUIButton::Ptr button)
{
	getStateManager().pushState(std::make_shared<Game>(getStateManager()));
}

void MainMenu::handleEvents(sf::Event& ev)
{
	mGuiBox->handleEvent(ev);
}

void MainMenu::render(Display& display)
{
	display.setToDefaultView();
	mGuiBox->render(display);
}

void MainMenu::update()
{

}

bool MainMenu::isAlive()
{
	return true;
}