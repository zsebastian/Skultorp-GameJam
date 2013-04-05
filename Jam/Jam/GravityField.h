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
	void addObject(std::shared_ptr<Entity>);

	void removeObject(std::shared_ptr<Entity>);

	void update();

private:
	std::vector<std::shared_ptr<Ball>> mBalls;
	std::shared_ptr<Cat> mCat;
	float mGravityForce;

};

#endif