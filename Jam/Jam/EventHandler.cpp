#include "EventHandler.h"
#include "EventManager.h"

EventHandler::EventHandler(sf::Event::EventType eventType, std::function<void (sf::Event&)> eventFunction)
{
	EventManager::getInstance()->registerEventHandler(this, eventType, eventFunction);
}

EventHandler::~EventHandler()
{
	EventManager::getInstance()->unregisterEventHandler(this);
}