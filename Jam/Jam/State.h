#ifndef STATE_H
#define STATE_H

#include <SFML\System\NonCopyable.hpp>

class State: public sf::NonCopyable
{
public:
	virtual ~State();
	void render(){};
	void update(){};
	bool isAlive(){return true;};
private:
	
};

#endif