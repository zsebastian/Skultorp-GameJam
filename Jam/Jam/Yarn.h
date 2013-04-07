#ifndef YARN_H
#define YARN_H

#include <vector>
#include "Display.h"
#include <SFML\System\Vector2.hpp>
#include <SFML\Graphics\Texture.hpp>

struct Bezier
{
	sf::VertexArray vertices;
	sf::FloatRect rect;
	sf::Texture* texture;

	Bezier(sf::VertexArray vertices, sf::FloatRect rect, sf::Texture* texture)
		:vertices(vertices)
		,rect(rect)
		,texture(texture)
	{};

};

class Yarn
{
public:
	Yarn();

	void updatePosition(sf::Vector2f position, bool add = true);
	void render(Display& display);

	bool intersect(sf::Vector2f position, float radius);

	void setTexture(sf::Texture* texture);

private:
	void addThread();
	bool intersectLineCircle(sf::Vector2f linePoint0, sf::Vector2f linePoint1, sf::Vector2f circlePosition, float radius);

	sf::VertexArray makeBezier(sf::Vector2f from, sf::Vector2f to, sf::Vector2f controlA, sf::Vector2f controlB);

	sf::Vector2f mPosition;
	std::vector<sf::Vector2f> mThreads;
	int mFrameCounter;
	

	bool mRed;

	std::vector<Bezier> mBeziers;
	int currentBezierIndex;

	sf::Texture mTexture;

	sf::Texture* mCurrentTexture;

	float mTotalLength;
	float mLatestThreadLength;
	const float mThreadingLength;
	size_t mGraceThreads;

	float getTextureY();

};

#endif