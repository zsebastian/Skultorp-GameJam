#ifndef YARN_H
#define YARN_H

#include <vector>
#include "Display.h"
#include <SFML\System\Vector2.hpp>

struct Bezier
{
	sf::VertexArray vertices;
	sf::FloatRect rect;

	Bezier(sf::VertexArray vertices, sf::FloatRect rect)
		:vertices(vertices)
		,rect(rect) {};

};

class Yarn
{
public:
	Yarn();

	void updatePosition(sf::Vector2f position, bool add = true);
	void render(Display& display);
private:
	void addThread();
	
	sf::VertexArray makeBezier(sf::Vector2f from, sf::Vector2f to, sf::Vector2f controlA, sf::Vector2f controlB);

	sf::Vector2f mPosition;
	std::vector<sf::Vector2f> mThreads;
	int mFrameCounter;
	const int mThreadingDelay;

	bool mRed;

	std::vector<Bezier> mBeziers;
	int currentBezierIndex;
};

#endif