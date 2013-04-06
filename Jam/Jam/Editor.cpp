#include "Editor.h"
#include "Display.h"
#include "Entity.h"
#include "Ball.h"
#include "EntityManager.h"
#include "Utility.h"
#include "tinyxml2.h"

Editor::Editor(EntityManager* entityManager)
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

	//Get mouse position
	mMousePosition = display.getWindow().convertCoords(sf::Mouse::getPosition(display.getWindow()), display.getCamera().getView());
	mPotentialEntity.setPosition(mMousePosition);

	display.render(mPotentialEntity);
}

void Editor::onButtonDown(sf::Event& e)
{
	if(!mLockedOnEntity)
	{
		if(e.mouseButton.button == sf::Mouse::Left)
		{
			for(EntityVec::iterator i = mEntities.begin(); i != mEntities.end(); i++)
			{
				if((*i)->getGlobalBounds().contains(mMousePosition))
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
			mEntityManager->pushEntity(std::make_shared<Ball>(mMousePosition, radius, radius));
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
	//Set position for locked entity
	if(mLockedOnEntity && mCurrentEntity != nullptr)
		mCurrentEntity->setPosition(mMousePosition);
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

	//Save level
	if(e.key.code == sf::Keyboard::F12)
	{
		saveLevel("data/levels/test.xml");
	}
}

void Editor::saveLevel(const std::string& filename)
{
	tinyxml2::XMLDocument doc;

	tinyxml2::XMLElement* level = doc.NewElement("level");
	tinyxml2::XMLElement* balls = doc.NewElement("balls");

	//Append all the balls
	for(auto i = mEntities.begin(); i != mEntities.end(); ++i)
	{
		std::shared_ptr<Ball> b = std::dynamic_pointer_cast<Ball>(*i);
		
		if(b == nullptr)
			continue;

		tinyxml2::XMLElement* ball = doc.NewElement("ball");
		sf::Vector2f position = b->getPosition();
		ball->SetAttribute("x", position.x);
		ball->SetAttribute("y", position.y);
		ball->SetAttribute("mass", b->getMass());
		ball->SetAttribute("radius", b->getRadius());
		balls->InsertEndChild(ball);
	}

	//Append to level
	level->InsertEndChild(balls);

	//Append declaration and level to document
	doc.InsertEndChild(doc.NewDeclaration());
	doc.InsertEndChild(level);

	doc.SaveFile(filename.c_str());
}