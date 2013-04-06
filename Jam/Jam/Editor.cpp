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
	
}