#ifndef CAMERA_H
#define CAMERA_H

#include <SFML/Graphics/View.hpp>
#include <SFML/Graphics/RenderWindow.hpp>

class Camera
{
public:
	Camera(const sf::Vector2f& size, const sf::Vector2f& position, float scale = 1.f);

	void setPosition(const sf::Vector2f& position);
	void setRotation(float rotation);
	void setScale(float scale);

	sf::Vector2f getPosition() const;
	float getRotation() const;
	float getScale() const;
	sf::View& getView();
private:
	sf::View mView;
	sf::Vector2f mOriginalSize;
	float mScale;
};

#endif