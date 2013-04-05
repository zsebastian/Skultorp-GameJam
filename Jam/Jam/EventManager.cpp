#include "EventManager.h"
#include <assert.h>

EventManager::EventManager()
{

}

EventManager* EventManager::getInstance()
{
	static EventManager mThisIsAnInstanceFucker;
	return &mThisIsAnInstanceFucker;
}

void EventManager::newEvent(sf::Event& ev)
{
	for (auto eventHandler: mEventHandlers)
	{
		eventHandler.second(ev);
	}
}

void EventManager::registerEventHandler(EventHandler* handler, std::function<void (sf::Event&)> function)
{
	assert(mEventHandlers.count(handler) == 0);
	mEventHandlers[handler] = function;
}
void EventManager::unregisterEventHandler(EventHandler* handler)
{
	mEventHandlers.erase(handler);
}
