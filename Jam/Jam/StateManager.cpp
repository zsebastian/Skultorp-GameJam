#include "StateManager.h"
#include <algorithm>

StateManager::StateManager()
	:msElapsed(0.f)
	,msUpdateRate(10.f)
{
	clock.restart();
}

void StateManager::pushState(std::shared_ptr<State> state)
{
	//when pushing a state we must retart our clock
	mStateStack.push_back(state);
	clock.restart();
}

void StateManager::update()
{
	//If empty do nothing
	if (mStateStack.empty())
		return;

	//remove dead states
	auto pred = [](std::shared_ptr<State> state) {return state->isAlive();};
	mStateStack.erase(
		std::remove_if(mStateStack.begin(), mStateStack.end(), pred),
		mStateStack.end());

	//update state using a defined timestep
	for (msElapsed += clock.restart().asMilliseconds(); msElapsed > msUpdateRate; msElapsed -= msUpdateRate)
	{
		mStateStack.back()->update();
	}
}

void StateManager::render(Display& display)
{
	if (!mStateStack.empty())
		mStateStack.back()->render(display);

}