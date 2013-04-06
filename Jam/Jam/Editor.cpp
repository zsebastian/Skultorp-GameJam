#include "Editor.h"
#include "Display.h"
#include "Entity.h"

Editor::Editor()
	:EventHandler(sf::Event::MouseButtonPressed, std::bind(&Editor::onButtonDown, this, std::placeholders::_1))
{

}

Editor::~Editor()
{

}

void Editor::pushEntity(std::shared_ptr<Entity> entity)
{
	mEntities.push_back(entity);
}

void Editor::update()
{

}

void Editor::render(Display& display)
{

}

void Editor::onButtonDown(sf::Event& e)
{
	if(mLockedOnEntity)
		return;

	if(e.mouseButton.button == sf::Mouse::Left)
	{
		sf::Vector2f mousePos(e.mouseButton.x, e.mouseButton.y);

		for(EntityVec::iterator i = mEntities.begin(); i != mEntities.end(); i++)
		{
			if((*i)->getGlobalBounds().contains(mousePos))
			{
				mCurrentEntity = *i;
				mLockedOnEntity = true;
			}
		}
	}
}


void Editor::onButtonUp(sf::Event& e)
{
	if(e.mouseButton.button == sf::Mouse::Left)
	{
		mLockedOnEntity = false;
		mCurrentEntity = nullptr;
	}
}

void Editor::onMouseMove(sf::Event& e)
{
	if(mLockedOnEntity)
	{
		sf::Vector2f mousePos(e.mouseButton.x, e.mouseButton.y);
		
		if(mCurrentEntity)
			mCurrentEntity->setPosition(mousePos);
	}
}