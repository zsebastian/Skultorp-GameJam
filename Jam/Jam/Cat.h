#ifndef CAT_H
#define CAT_H

#include "Entity.h"
#include <SFML/Graphics/CircleShape.hpp>
#include <memory>
#include "AnimationManager.h"
#include "Yarn.h"


class Ball;

class Cat : public Entity
{
public:
	Cat(const sf::Vector2f& position = sf::Vector2f(), float mass = 10.f, float radius = 20.f);

	virtual ~Cat();

	virtual void setPosition(const sf::Vector2f& position);
	virtual void setMass(float mass);
	virtual void setRadius(float radius);
	virtual void update();
	virtual void render(Display& display);
	virtual void onCollision(std::shared_ptr<Entity> entity);
	void setGravityVector(const sf::Vector2f& gravityVector);

	std::vector<std::shared_ptr<Ball>>& standsOnPlanets();
	void resetStandsOn();

	virtual sf::Vector2f getPosition() const;
	virtual float getMass() const;
	virtual float getRadius() const;
	virtual sf::FloatRect getGlobalBounds() const;
private:
	sf::Vector2f mPosition;
	sf::Vector2f mGravityVector;
	sf::Vector2f mRightVector;
	sf::Vector2f mMoveSpeed;
	sf::Vector2f mJumpDirection;

	float mWalkSpeed;

	float mMass;
	float mRadius;

	void move();
	void walk();
	
	//jumping
	void jump();
	void jumping();

	bool mCanJump;
	bool mJumping;
	float mMaxJumpPower;
	float mCurrentJumpPower;
	float mJumpDecelaration;

	sf::CircleShape mTempShape;

	std::shared_ptr<Ball> mStandingOn;

	std::vector<std::shared_ptr<Ball>> mStandsOn;


	// animtion
	AnimationManager mAnimations;
	bool mLeftDir;

	Yarn mYarn;

	float mTargetCameraRotation;
};

#endif