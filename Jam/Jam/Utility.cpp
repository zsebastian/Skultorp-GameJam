#include "Utility.h"

int Util::random(int min, int max)
{
	return (std::rand() % (max-min)) + min;
}