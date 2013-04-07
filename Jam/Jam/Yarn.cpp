#include "Yarn.h"
#include "Display.h"
#include "Utility.h"
#include <math.h>

Yarn::Yarn()
	:mThreadingLength(10.f)
	,mTotalLength(0.f)
	,mLatestThreadLength(0.f)
	,mGraceThreads(15)
	,mQuadWidth(5.f)
	,mCurveFreq(0.1f)
{
	currentBezierIndex = 0;
	
	mCurrentTexture = nullptr;
}

void Yarn::updatePosition(sf::Vector2f position, bool add)
{
	if (mCurrentTexture == nullptr)
	{
		mLatestThreadLength = 0.f;
	}
	else
	{
		mLatestThreadLength += Util::length(mPosition - position);

		mPosition = position;
		if (mLatestThreadLength > mThreadingLength)
		{
			mLatestThreadLength = 0.f;
			mFrameCounter = 0;
			addThread();
		}
	}
}

void Yarn::render(Display& display)
{
	mRed = true;

	if (mThreads.empty() || mCurrentTexture == nullptr)
		return;

	sf::Vector2f last = mThreads[currentBezierIndex].first;

	//not really a loop but whatevs

	if (currentBezierIndex < static_cast<int>(mThreads.size()) - 4)
	{
		int i = currentBezierIndex;
		sf::VertexArray bezier = makeBezier(last, mThreads[i + 1].first, mThreads[i + 2].first, mThreads[i + 3].first);

		//glue
		if (currentBezierIndex > 0 && bezier.getVertexCount() >= 2 && mBeziers.back().vertices.getVertexCount() > 2)
		{
			sf::Vector2f textSize = static_cast<sf::Vector2f>(mTexture.getSize());

			sf::VertexArray& last = mBeziers.back().vertices;
			sf::Vector2f p0(last[last.getVertexCount() - 1].position);
			sf::Vector2f p1(last[last.getVertexCount() - 2].position);
			sf::Vector2f p2(bezier[0].position);
			sf::Vector2f p3(bezier[1].position);

			mBeziers.back().vertices.append(sf::Vertex(p0, sf::Vector2f(0.f, getTextureY())));
			mBeziers.back().vertices.append(sf::Vertex(p1, sf::Vector2f(textSize.x, getTextureY())));


			mBeziers.back().vertices.append(sf::Vertex(p3, sf::Vector2f(textSize.x, getTextureY())));
			mBeziers.back().vertices.append(sf::Vertex(p2, sf::Vector2f(0.f, getTextureY())));

		}

		for (size_t i = 0; i < bezier.getVertexCount(); ++i)
		{
			mBeziers.back().vertices.append(bezier[i]);
		}
		mBeziers.back().rect = mBeziers.back().vertices.getBounds();
	
		currentBezierIndex += 3;
	}


	for (auto iter = mBeziers.begin(); iter != mBeziers.end(); ++iter)
	{
		sf::RenderStates rend(iter->texture);

		display.render(iter->vertices, rend);
	}

	if (mThreads.size() > 3 && currentBezierIndex > 0 && mBeziers.back().vertices.getVertexCount() > 2)
	{
		//what to do to fill the void?;

		sf::VertexArray ret(sf::Quads);
		sf::Vector2f dir = last - mPosition;

		sf::Vector2f normal = Util::normalize(Util::getNormal(dir));
		sf::VertexArray& lastBez = mBeziers.back().vertices;

		sf::Vector2f p0 = mPosition - normal * mQuadWidth;
		sf::Vector2f p1 = mPosition + normal * mQuadWidth;
		sf::Vector2f p2 = lastBez[lastBez.getVertexCount() - 2].position;
		sf::Vector2f p3 = lastBez[lastBez.getVertexCount() - 1].position;
		
		float len = Util::length(p0 - p2);
		sf::Vector2f textSize;

		if (mCurrentTexture != nullptr)
			textSize = static_cast<sf::Vector2f>(mCurrentTexture->getSize());

		float y1 = std::fmod(mTotalLength, textSize.y);
		float y0 = std::fmod(mTotalLength + len, textSize.y);

		ret.append(sf::Vertex(p0, sf::Vector2f(0.f, y0)));
		ret.append(sf::Vertex(p1, sf::Vector2f(textSize.x, y0)));
		ret.append(sf::Vertex(p3, sf::Vector2f(textSize.x, y1)));
		ret.append(sf::Vertex(p2, sf::Vector2f(0.f, y1)));

		sf::RenderStates rend(mBeziers.back().texture);
		display.render(ret, rend);
	}
	
}

void Yarn::addThread()
{
	mThreads.push_back(std::make_pair(mPosition, mCurrentTexture));
}

sf::VertexArray Yarn::makeBezier(sf::Vector2f p0, sf::Vector2f p1, sf::Vector2f p2, sf::Vector2f p3)
{
	sf::VertexArray ret(sf::PrimitiveType::Quads);
	sf::Vector2f textSize;
	if (mCurrentTexture != nullptr)
		textSize = static_cast<sf::Vector2f>(mCurrentTexture->getSize());	

	std::vector<sf::Vector2f> plots;


	float qx, qy;
    float q1, q2, q3, q4;
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

        t = t + mCurveFreq;
    }

	sf::Vector2f prevp0;
	sf::Vector2f prevp1;
	sf::Vector2f dir = plots[0] - plots[1];
	sf::Vector2f normal = Util::normalize(Util::getNormal(dir));
	prevp0 = plots[0] + normal * mQuadWidth;
	prevp1 = plots[0] - normal * mQuadWidth;
	
	for (size_t i = 1; i < plots.size(); ++i)
	{
		sf::Vector2f dir = plots[i - 1] - plots[i];
		sf::Vector2f normal = Util::normalize(Util::getNormal(dir));
		
		sf::Vector2f p0 = plots[i] + normal * mQuadWidth;
		sf::Vector2f p1 = plots[i] - normal * mQuadWidth;

		float distance = Util::length(dir);

		if (Util::floatCompare(distance, 0.f))
			continue;

		ret.append(sf::Vertex(prevp0, sf::Vector2f(0.f, getTextureY())));
		ret.append(sf::Vertex(prevp1, sf::Vector2f(textSize.x, getTextureY())));
		mTotalLength += distance;

		ret.append(sf::Vertex(p1, sf::Vector2f(textSize.x, getTextureY())));
		ret.append(sf::Vertex(p0, sf::Vector2f(0.f, getTextureY())));
		
		prevp0 = p0;
		prevp1 = p1;

	}

	return ret;
}

float Yarn::getTextureY()
{
	if (mCurrentTexture == nullptr)
		return 0.f;

	return std::fmod(mTotalLength, static_cast<sf::Vector2f>(mCurrentTexture->getSize()).y);
}

bool Yarn::intersect(sf::Vector2f position, float radius)
{
	if (mThreads.size() > 1 && mThreads.size() > mGraceThreads)
	{
		for (size_t i = 1; i < mThreads.size() - mGraceThreads; ++i)
		{
			if (mThreads[i].second == mCurrentTexture && mThreads[i-1].second == mCurrentTexture )
				continue;

			sf::Vector2f v0 = mThreads[i - 1].first;
			sf::Vector2f v1 = mThreads[i].first;

			if (intersectLineCircle(v0, v1, position, radius))
				return true;
		}
	}

	return false;
}

bool Yarn::intersectLineCircle(sf::Vector2f linePoint0, sf::Vector2f linePoint1, sf::Vector2f circlePosition, float radius)
{
	//E is the starting point of the ray,
	//L is the end point of the ray,
	//C is the center of sphere you're testing against
	//r is the radius of that sphere

	//d = L - E ( Direction vector of ray, from start to end )
	//f = E - C ( Vector from center sphere to ray start )

	sf::Vector2f d = linePoint1 - linePoint0;
	sf::Vector2f f = linePoint0 - circlePosition;

	float a = Util::dot(d, d);
	float b = 2 * Util::dot(f, d);
	float c = Util::dot(f, f ) - radius * radius ;

	float discriminant = b*b-4*a*c;
	if( discriminant < 0 )
	{
		return false;
	}
	else
	{
		// ray didn't totally miss sphere,
		// so there is a solution to
		// the equation.

		discriminant = std::sqrt( discriminant );

		// either solution may be on or off the ray so need to test both
		// t1 is always the smaller value, because BOTH discriminant and
		// a are nonnegative.
		float t1 = (-b - discriminant)/(2*a);
		float t2 = (-b + discriminant)/(2*a);

		// 3x HIT cases:
		//          -o->             --|-->  |            |  --|->
		// Impale(t1 hit,t2 hit), Poke(t1 hit,t2>1), ExitWound(t1<0, t2 hit), 

		// 3x MISS cases:
		//       ->  o                     o ->              | -> |
		// FallShort (t1>1,t2>1), Past (t1<0,t2<0), CompletelyInside(t1<0, t2>1)

		if( t1 >= 0 && t1 <= 1 )
		{
		// t1 is an intersection, and if it hits,
		// it's closer than t2 would be
		// Impale, Poke
		return true ;
		}

		// here t1 didn't intersect so we are either started
		// inside the sphere or completely past it
		if( t2 >= 0 && t2 <= 1 )
		{
		// ExitWound
		return true ;
		}

		// no intn: FallShort, Past, CompletelyInside
		return false ;
	}
}

void Yarn::setTexture(sf::Texture* texture)
{
	mCurrentTexture = texture;
	mBeziers.push_back(Bezier(sf::VertexArray(sf::PrimitiveType::Quads), sf::FloatRect(), mCurrentTexture));
}