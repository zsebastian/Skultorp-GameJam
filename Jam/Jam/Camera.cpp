#include "Camera.h"

Camera::Camera(const sf::Vector2f& size, const sf::Vector2f& position, float scale)
	:mOriginalSize(size)
	,mScale(scale)
{
	mView.setSize(size);
	mView.setCenter(position);
}

void Camera::setPosition(const sf::Vector2f& position)
{
	mView.setCenter(position);
}

void Camera::move(const sf::Vector2f& delta)
{
	setPosition(getPosition() + delta);
}

void Camera::setRotation(float rotation)
{
	mView.setRotation(rotation);
}

void Camera::rotate(float delta)
{
	setRotation(getRotation() + delta);
}

void Camera::setScale(float scale)
{
	mScale = scale;
	mView.setSize(mOriginalSize*scale);
}

sf::Vector2f Camera::getPosition() const
{
	return mView.getCenter();
}

float Camera::getRotation() const
{
	return mView.getRotation();
}

float Camera::getScale() const
{
	return mScale;
}

sf::View& Camera::getView()
{
	return mView;
}