#include "Editor.h"
#include "Display.h"
#include "Entity.h"
#include "Ball.h"
#include "EntityManager.h"
#include "Utility.h"

Editor::Editor(std::shared_ptr<EntityManager> entityManager)
{
	//Register events
	mEventHandler.addEventListener(sf::Event::MouseButtonPressed, std::bind(&Editor::onButtonDown, this, std::placeholders::_1));
	mEventHandler.addEventListener(sf::Event::MouseButtonReleased, std::bind(&Editor::onButtonUp, this, std::placeholders::_1));
	mEventHandler.addEventListener(sf::Event::MouseMoved, std::bind(&Editor::onMouseMove, this, std::placeholders::_1));
	mEventHandler.addEventListener(sf::Event::KeyPressed, std::bind(&Editor::onKeyDown, this, std::placeholders::_1));

	mEntityManager = entityManager;

	float radius = 20.f;
	mPotentialEntity.setRadius(radius);
	mPotentialEntity.setOrigin(radius, radius);
	mPotentialEntity.setFillColor(sf::Color(0, 255, 0, 100));
}

Editor::~Editor()
{

}

void Editor::pushEntity(std::shared_ptr<Entity> entity)
{
	mEntities.push_back(entity);
}

void Editor::popEntity(std::shared_ptr<Entity> entity)
{
	auto pred = [&entity](std::shared_ptr<Entity> someEntity) {return someEntity.get() == entity.get();};
	Util::eraseIf(mEntities, pred);
}

void Editor::update()
{
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Add))
	{
		float radius = mPotentialEntity.getRadius();
		mPotentialEntity.setRadius(radius + 1 );
		mPotentialEntity.setOrigin(radius, radius);
	}
	else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Subtract))
	{
		float radius = mPotentialEntity.getRadius();
		mPotentialEntity.setRadius(radius - 1 );
		mPotentialEntity.setOrigin(radius, radius);
	}
}

void Editor::render(Display& display)
{
	//display.getCamera().setRotation(0.f);
	display.render(mPotentialEntity);
}

void Editor::onButtonDown(sf::Event& e)
{
	sf::Vector2f mousePos(static_cast<float>(e.mouseButton.x), static_cast<float>(e.mouseButton.y));

	if(!mLockedOnEntity)
	{
		if(e.mouseButton.button == sf::Mouse::Left)
		{
			for(EntityVec::iterator i = mEntities.begin(); i != mEntities.end(); i++)
			{
				if((*i)->getGlobalBounds().contains(mousePos))
				{
					mCurrentEntity = *i;
					mLockedOnEntity = true;
				}
			}
		}
		else if(e.mouseButton.button == sf::Mouse::Middle)
		{
			//Add new ball
			float radius = mPotentialEntity.getRadius();
			mEntityManager->pushEntity(std::make_shared<Ball>(mousePos, radius, radius));
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
	sf::Vector2f mousePos(static_cast<float>(e.mouseMove.x), static_cast<float>(e.mouseMove.y));

	//Set position for locked entity
	if(mLockedOnEntity && mCurrentEntity != nullptr)
		mCurrentEntity->setPosition(mousePos);

	mPotentialEntity.setPosition(mousePos);
}

void Editor::onKeyDown(sf::Event& e)
{
	//Remove entity
	if(mLockedOnEntity && e.key.code == sf::Keyboard::Delete)
	{
		mEntityManager->popEntity(mCurrentEntity);
		mCurrentEntity = nullptr;
		mLockedOnEntity = false;
	}
}