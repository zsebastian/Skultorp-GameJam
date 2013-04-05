#ifndef STATE_H
#define STATE_H

#include <SFML\System\NonCopyable.hpp>

class State: public sf::NonCopyable
{
public:
	virtual ~State() {};
	virtual void render() = 0;
	virtual void update() = 0;
	virtual bool isAlive() = 0;
private:
	
};

#endif