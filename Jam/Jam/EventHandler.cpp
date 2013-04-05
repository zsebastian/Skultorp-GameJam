#include "EventHandler.h"
#include "EventManager.h"

EventHandler::EventHandler(std::function<void (sf::Event&)> eventFunction)
{
	EventManager::getInstance()->registerEventHandler(this, eventFunction);
}

EventHandler::~EventHandler()
{
	EventManager::getInstance()->unregisterEventHandler(this);
}