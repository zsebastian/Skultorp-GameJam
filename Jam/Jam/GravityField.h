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
	GravityField(float gravityForce);
	void addObject(std::shared_ptr<Ball>);
	void addObject(std::shared_ptr<Cat>);

	void removeObject(std::shared_ptr<Ball>);
	void removeObject(std::shared_ptr<Cat>);

	void update();

private:
	std::vector<std::shared_ptr<Ball>> mBalls;
	std::shared_ptr<Cat> mCat;
	float mGravityForce;

	float distance(sf::Vector2f, sf::Vector2f);
	sf::Vector2f normalize(sf::Vector2f);
	float length(sf::Vector2f);
};

#endif