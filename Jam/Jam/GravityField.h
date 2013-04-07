#ifndef GRAVITYFIELD_H
#define GRAVITYFIELD_H

#include <memory>
#include <vector>
#include <SFML\System\Vector2.hpp>

class Entity;
class Cat;
class Ball;

class GravityField
{
public:

	GravityField(float gravityForce = 100.f, float terminalVelocity = 5.f);

	void addObject(std::shared_ptr<Entity>);
	void removeObject(std::shared_ptr<Entity>);
	void clear();

	void update();

private:
	std::vector<std::shared_ptr<Ball>> mBalls;
	std::vector<std::shared_ptr<Cat>> mCats;
	
	sf::Vector2f calcGravity(std::shared_ptr<Entity>, std::shared_ptr<Entity>) const;

	float mGravityForce;
	float mTerminalVelocity;
	};

#endif