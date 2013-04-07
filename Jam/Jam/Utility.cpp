#include "Utility.h"

int Util::random(int min, int max)
{
	return (std::rand() % (max-min)) + min;
}

float Util::angleInRange(float angle)
{
	angle = std::fmod(angle, 360.f);

	if (angle < 0)
	{
		angle = 360.f + angle ;
	}

	return angle;
}

float Util::shortestAngleDistance(float targetAngle, float currentAngle)
{
	float shortestDist = targetAngle - currentAngle;

	while(shortestDist < -180)
	{
		shortestDist += 360;
	}
	while(shortestDist > 180)
	{
		shortestDist -= 360;
	}
	return shortestDist;
}