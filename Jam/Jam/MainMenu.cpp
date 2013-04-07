#include "MainMenu.h"
#include "StateManager.h"
#include <memory>
#include "Game.h"

MainMenu::MainMenu(StateManager& stateManager)
	:State(stateManager)
	,mGuiBox(GUIBox::create(sf::FloatRect(0.f, 0.f, 800.f, 600.f)))
	,mIsAlive(true)
{
	mButtonTexture.loadFromFile("data/menubuttons.png");

	GUIButton::Ptr start = GUIButton::create(sf::FloatRect(10.f, 10.f, 512.f, 256.f), sf::Sprite(mButtonTexture, sf::IntRect(0, 0, 512, 256)));
	start->setOnMouseHoverSprite(sf::Sprite(mButtonTexture, sf::IntRect(512, 0, 512, 256)));
	start->setOnMouseDownSprite(sf::Sprite(mButtonTexture, sf::IntRect(1028, 0, 512, 256)));

	start->setOnMouseUpFunction(std::bind(&MainMenu::startGame, this, std::placeholders::_1));
	mGuiBox->addChild(start);

	GUIButton::Ptr options = GUIButton::create(sf::FloatRect(10.f, 10.f + 256.f, 512.f, 256.f), sf::Sprite(mButtonTexture, sf::IntRect(0, 256, 512, 256)));
	options->setOnMouseHoverSprite(sf::Sprite(mButtonTexture, sf::IntRect(512, 256, 512, 256)));
	options->setOnMouseDownSprite(sf::Sprite(mButtonTexture, sf::IntRect(1028, 256, 512, 256)));

	options->setOnMouseUpFunction(std::bind(&MainMenu::startOptions, this, std::placeholders::_1));
	mGuiBox->addChild(options);

	GUIButton::Ptr exit = GUIButton::create(sf::FloatRect(10.f, 10.f + 512.f, 512.f, 256.f), sf::Sprite(mButtonTexture, sf::IntRect(0, 512, 512, 256)));
	exit->setOnMouseHoverSprite(sf::Sprite(mButtonTexture, sf::IntRect(512, 512, 512, 256)));
	exit->setOnMouseDownSprite(sf::Sprite(mButtonTexture, sf::IntRect(1028, 512, 512, 256)));

	exit->setOnMouseUpFunction(std::bind(&MainMenu::exitGame, this, std::placeholders::_1));
	mGuiBox->addChild(exit);

	std::function<void (sf::Event&)> handler = std::bind(&MainMenu::handleEvents, this, std::placeholders::_1);

	eventHandler.addEventListener(sf::Event::MouseButtonPressed, handler);
	eventHandler.addEventListener(sf::Event::MouseButtonReleased, handler);
	eventHandler.addEventListener(sf::Event::MouseMoved, handler);

}

void MainMenu::startGame(GUIButton::Ptr button)
{
	getStateManager().pushState(std::make_shared<Game>(getStateManager()));
}

void MainMenu::startOptions(GUIButton::Ptr button)
{

}


void MainMenu::exitGame(GUIButton::Ptr button)
{
	mIsAlive = false;
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
	return mIsAlive;
}