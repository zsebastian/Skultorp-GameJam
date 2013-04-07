#ifndef GAME_H
#define GAME_H

#include "State.h"
#include "EntityManager.h"
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Sprite.hpp>

class Game : public State
{
public:
	Game(StateManager& stateManager);
	virtual void render(Display&);
	virtual void update();
	virtual bool isAlive();
private:
	EntityManager entities;

	sf::Texture mBackgroundTexture;
	sf::Sprite mBackgroundSprite;

	void loadLevel(const std::string& filename);
};

#endif