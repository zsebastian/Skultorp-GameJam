#include "Yarn.h"
#include "Display.h"
#include "Utility.h"

Yarn::Yarn()
	:mThreadingDelay(5)
{
	mFrameCounter = mThreadingDelay;
	currentBezierIndex = 0;
	mTexture.loadFromFile("data/thread.png");
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

	//not really a loop but whatevs
	for (currentBezierIndex; currentBezierIndex < static_cast<int>(mThreads.size()) - 4; currentBezierIndex += 3)
	{

		int i = currentBezierIndex;
		sf::VertexArray bezier = makeBezier(last, mThreads[i + 1], mThreads[i + 2], mThreads[i + 3]);

		//glue
		if (currentBezierIndex > 0)
		{
			sf::Vector2f textSize = static_cast<sf::Vector2f>(mTexture.getSize());

			sf::VertexArray& last = mBeziers.back().vertices;
			sf::Vector2f p0(last[last.getVertexCount() - 1].position);
			sf::Vector2f p1(last[last.getVertexCount() - 2].position);
			sf::Vector2f p2(bezier[0].position);
			sf::Vector2f p3(bezier[1].position);

			float textY0 = last[last.getVertexCount() - 1].texCoords.y + last[0].texCoords.y;;
			float textY1 = textY0 + last[0].texCoords.y;
			
			mBeziers.back().vertices.append(sf::Vertex(p0, sf::Vector2f(0.f, textY0)));
			mBeziers.back().vertices.append(sf::Vertex(p1, sf::Vector2f(textSize.x, textY0)));
			mBeziers.back().vertices.append(sf::Vertex(p3, sf::Vector2f(textSize.x, textY1)));
			mBeziers.back().vertices.append(sf::Vertex(p2, sf::Vector2f(0.f, textY1)));

		}
		mBeziers.push_back(Bezier(bezier, bezier.getBounds()));
	}

	sf::RenderStates rend(&mTexture);

	for (auto iter = mBeziers.begin(); iter != mBeziers.end(); ++iter)
	{
		display.render(iter->vertices, rend);
	}

	if (mThreads.size() > 3 && currentBezierIndex > 0)
	{
		//what to do to fill the void?;

		sf::VertexArray ret(sf::Quads);
		sf::Vector2f dir = last - mPosition;

		sf::Vector2f normal = Util::normalize(Util::getNormal(dir));
		sf::VertexArray& lastBez = mBeziers.back().vertices;

		sf::Vector2f p0 = mPosition - normal * 5.f;
		sf::Vector2f p1 = mPosition + normal * 5.f;
		sf::Vector2f p2 = lastBez[lastBez.getVertexCount() - 2].position;
		sf::Vector2f p3 = lastBez[lastBez.getVertexCount() - 1].position;
		
		sf::Vector2f textSize = static_cast<sf::Vector2f>(mTexture.getSize());

		ret.append(sf::Vertex(p0, sf::Vector2f(0.f, 0.f)));
		ret.append(sf::Vertex(p1, sf::Vector2f(textSize.x, 0.f)));
		ret.append(sf::Vertex(p3, sf::Vector2f(textSize.x, textSize.y)));
		ret.append(sf::Vertex(p2, sf::Vector2f(0.f, textSize.y)));

		display.render(ret, rend);
	}
	
}

void Yarn::addThread()
{
	mThreads.push_back(mPosition);
}

sf::VertexArray Yarn::makeBezier(sf::Vector2f p0, sf::Vector2f p1, sf::Vector2f p2, sf::Vector2f p3)
{
	sf::VertexArray ret(sf::PrimitiveType::Quads);
	sf::Vector2f textSize = static_cast<sf::Vector2f>(mTexture.getSize());	
	std::vector<sf::Vector2f> plots;

	const float quadWidth = 5.f;
	const float curveFreq = 0.1f;
	float qx, qy;
    float q1, q2, q3, q4;
    float plotx, ploty;
    float t = 0.0;

	q1 = t*t*t*-1 + t*t*3 + t*-3 + 1;
    q2 = t*t*t*3 + t*t*-6 + t*3;
    q3 = t*t*t*-3 + t*t*3;
    q4 = t*t*t;

	qx = q1*p0.x + q2*p1.x + q3*p2.x + q4*p3.x;
	qy = q1*p0.y + q2*p1.y + q3*p2.y + q4*p3.y;

    while (t <= 1)
    {
        q1 = t*t*t*-1 + t*t*3 + t*-3 + 1;
        q2 = t*t*t*3 + t*t*-6 + t*3;
        q3 = t*t*t*-3 + t*t*3;
        q4 = t*t*t;

		qx = q1*p0.x + q2*p1.x + q3*p2.x + q4*p3.x;
		qy = q1*p0.y + q2*p1.y + q3*p2.y + q4*p3.y;

		plots.push_back(sf::Vector2f(qx, qy));

        t = t + curveFreq;
    }

	sf::Vector2f prevp0;
	sf::Vector2f prevp1;
	sf::Vector2f dir = plots[0] - plots[1];
	sf::Vector2f normal = Util::normalize(Util::getNormal(dir));
	prevp0 = plots[0] + normal * quadWidth;
	prevp1 = plots[0] - normal * quadWidth;
	
	float textWalk = textSize.y / (plots.size()); // save 1 for the glue
	
	for (size_t i = 1; i < plots.size(); ++i)
	{
		sf::Vector2f dir = plots[i - 1] - plots[i];
		sf::Vector2f normal = Util::normalize(Util::getNormal(dir));
		
		sf::Vector2f p0 = plots[i] + normal * quadWidth;
		sf::Vector2f p1 = plots[i] - normal * quadWidth;

		ret.append(sf::Vertex(prevp0, sf::Vector2f(0.f, textWalk * i)));
		ret.append(sf::Vertex(prevp1, sf::Vector2f(textSize.x, textWalk * i)));
		ret.append(sf::Vertex(p1, sf::Vector2f(textSize.x, textWalk * (i - 1))));
		ret.append(sf::Vertex(p0, sf::Vector2f(0.f, textWalk * (i - 1))));

		prevp0 = p0;
		prevp1 = p1;

	}

	return ret;
}
