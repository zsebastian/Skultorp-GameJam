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
<<<<<<< HEAD
	GravityField(float gravityForce);
	void addObject(std::shared_ptr<Entity>);
=======
	GravityField(float gravityForce = 1.f);
	void addObject(std::shared_ptr<Ball>);
	void addObject(std::shared_ptr<Cat>);
>>>>>>> 5a632a71645147d3fa6577815451299287602d92

	void removeObject(std::shared_ptr<Entity>);

	void update();

private:
	std::vector<std::shared_ptr<Ball>> mBalls;
	std::shared_ptr<Cat> mCat;
	float mGravityForce;

};

#endif