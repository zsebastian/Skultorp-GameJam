#include "Editor.h"
#include "Display.h"
#include "Entity.h"
#include "Ball.h"
#include "LooseEnd.h"
#include "Cat.h"
#include "EntityManager.h"
#include "Utility.h"
#include "tinyxml2.h"

Editor::Editor(EntityManager* entityManager)
	:mCurrentIndex(0)
	,mLockedOnEntity(false)
	
{
	//Register events
	mEventHandler.addEventListener(sf::Event::MouseButtonPressed, std::bind(&Editor::onButtonDown, this, std::placeholders::_1));
	mEventHandler.addEventListener(sf::Event::MouseButtonReleased, std::bind(&Editor::onButtonUp, this, std::placeholders::_1));
	mEventHandler.addEventListener(sf::Event::MouseMoved, std::bind(&Editor::onMouseMove, this, std::placeholders::_1));
	mEventHandler.addEventListener(sf::Event::MouseWheelMoved, std::bind(&Editor::onMouseWheel, this, std::placeholders::_1));
	mEventHandler.addEventListener(sf::Event::KeyPressed, std::bind(&Editor::onKeyDown, this, std::placeholders::_1));

	mEntityManager = entityManager;

	float radius = 20.f;
	mPotentialEntity.setRadius(radius);
	mPotentialEntity.setOrigin(radius, radius);
	mPotentialEntity.setFillColor(sf::Color(0, 255, 0, 100));

	mYarnTypes.push_back(YarnType(0, 1.0f, 1.5f));
	mYarnTypes.push_back(YarnType(1, 1.0f, 1.5f));
	mYarnTypes.push_back(YarnType(2, 1.0f, 1.5f));
	mYarnTypes.push_back(YarnType(3, 1.0f, 1.5f));
	mYarnTypes.push_back(YarnType(4, 1.0f, 1.5f));


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

void Editor::clear()
{
	mEntities.clear();
}

void Editor::update()
{

}

void Editor::render(Display& display)
{
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
					break;
				}
			}
		}
		else if(e.mouseButton.button == sf::Mouse::Right)
		{
			//Add new ball
			float radius = mPotentialEntity.getRadius();
			std::shared_ptr<Ball> ball = std::make_shared<Ball>(mMousePosition, radius * mSelectedYarn.massModifier, radius * mSelectedYarn.radiusModifer, mSelectedYarn.index);
			mEntityManager->pushEntity(ball);
			mEntityManager->pushEntity(std::make_shared<LooseEnd>(ball, 45));
			mCurrentIndex++;
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
		if(std::dynamic_pointer_cast<Cat>(mCurrentEntity))
			return;

		mEntityManager->popEntity(mCurrentEntity);
		mCurrentEntity = nullptr;
		mLockedOnEntity = false;
		mCurrentIndex--;
	}

	//Save level
	if(e.key.code == sf::Keyboard::F1)
	{
		saveLevel(mEntityManager->getLevelFilename());
	}

	switch (e.key.code)
	{
	case sf::Keyboard::Num1:
		mSelectedYarn = mYarnTypes[0];
		break;
	case sf::Keyboard::Num2:
		mSelectedYarn = mYarnTypes[1];
		break;
	case sf::Keyboard::Num3:
		mSelectedYarn = mYarnTypes[2];
		break;
	case sf::Keyboard::Num4:
		mSelectedYarn = mYarnTypes[3];
		break;
	case sf::Keyboard::Num5:
		mSelectedYarn = mYarnTypes[4];
		break;
	}
}

void Editor::onMouseWheel(sf::Event& e)
{
	float radius = mPotentialEntity.getRadius() + e.mouseWheel.delta*4;
	mPotentialEntity.setRadius(radius);
	mPotentialEntity.setOrigin(radius, radius);
}

void Editor::saveLevel(const std::string& filename)
{
	tinyxml2::XMLDocument doc;

	tinyxml2::XMLElement* level = doc.NewElement("level");
	tinyxml2::XMLElement* balls = doc.NewElement("balls");

	//Append all the balls
	int ballCount = 0;

	for(auto i = mEntities.begin(); i != mEntities.end(); ++i)
	{
		std::shared_ptr<Ball> b = std::dynamic_pointer_cast<Ball>(*i);
		std::shared_ptr<Cat> c = std::dynamic_pointer_cast<Cat>(*i);

		if(c)
		{
			tinyxml2::XMLElement* cat = doc.NewElement("cat");
			sf::Vector2f position = c->getPosition();
			cat->SetAttribute("x", position.x);
			cat->SetAttribute("y", position.y);
			level->InsertEndChild(cat);
			continue;
		}

		if(b == nullptr)
			continue;

		tinyxml2::XMLElement* ball = doc.NewElement("ball");
		sf::Vector2f position = b->getPosition();
		ball->SetAttribute("x", position.x);
		ball->SetAttribute("y", position.y);
		ball->SetAttribute("mass", b->getMass());
		ball->SetAttribute("radius", b->getRadius());
		ball->SetAttribute("index", b->getIndexValue());

		//Add loose end
		tinyxml2::XMLElement* looseEnd = doc.NewElement("looseEnd");
		looseEnd->SetAttribute("angle", 0);
		ball->InsertEndChild(looseEnd);

		balls->InsertEndChild(ball);
		ballCount++;
	}

	//Add goal
	tinyxml2::XMLElement* goal = doc.NewElement("goal");
	goal->SetAttribute("value", ballCount);
	level->InsertEndChild(goal);

	//Append to level
	level->InsertEndChild(balls);

	//Append declaration and level to document
	doc.InsertEndChild(doc.NewDeclaration());
	doc.InsertEndChild(level);

	doc.SaveFile(filename.c_str());
}