#include "Yarn.h"
#include "Display.h"

Yarn::Yarn()
	:mThreadingDelay(10)
{
	mFrameCounter = mThreadingDelay;
	currentBezierIndex = 0;
}

void Yarn::updatePosition(sf::Vector2f position, bool add)
{
	++mFrameCounter;
	mPosition = position;
	if (mFrameCounter > mThreadingDelay)
	{
		mFrameCounter = 0;
		addThread();
	}
}

void Yarn::render(Display& display)
{
	mRed = true;

	sf::VertexArray vertices(sf::PrimitiveType::LinesStrip);
	if (mThreads.empty())
		return;

	sf::Vector2f last = mThreads[currentBezierIndex];

	for (currentBezierIndex; currentBezierIndex < static_cast<int>(mThreads.size()) - 4; currentBezierIndex += 3)
	{
		int i = currentBezierIndex;
		sf::VertexArray bezier = makeBezier(last, mThreads[i + 1], mThreads[i + 2], mThreads[i + 3]);

		mBeziers.push_back(Bezier(bezier, bezier.getBounds()));
		last = bezier[bezier.getVertexCount() - 1].position;
	}

	for (auto iter = mBeziers.begin(); iter != mBeziers.end(); ++iter)
	{
		display.render(iter->vertices);
	}

	if (mThreads.size() > 3)
	{
		//what to do to fill the void?;
		sf::Vector2f apa[4];

		sf::VertexArray ret(sf::LinesStrip);
		ret.append(last);
		ret.append(mPosition);

		display.render(ret);
	}
	
}

void Yarn::addThread()
{
	mThreads.push_back(mPosition);
}

sf::VertexArray Yarn::makeBezier(sf::Vector2f p0, sf::Vector2f p1, sf::Vector2f p2, sf::Vector2f p3)
{
	sf::VertexArray ret(sf::LinesStrip);
	
	float qx, qy;
    float q1, q2, q3, q4;
    float plotx, ploty;
    float t = 0.0;

    while (t <= 1)
    {
        q1 = t*t*t*-1 + t*t*3 + t*-3 + 1;
        q2 = t*t*t*3 + t*t*-6 + t*3;
        q3 = t*t*t*-3 + t*t*3;
        q4 = t*t*t;

		qx = q1*p0.x + q2*p1.x + q3*p2.x + q4*p3.x;
		qy = q1*p0.y + q2*p1.y + q3*p2.y + q4*p3.y;

        plotx = qx;
        ploty = qy;

		ret.append(sf::Vector2f(plotx, ploty));

        t = t + 0.01f;
    }
	return ret;
}
