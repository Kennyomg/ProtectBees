#include "../stdafx.h"
#include "VisibleGameObject.h"

VisibleGameObject::VisibleGameObject()
	: _isLoaded(false)
{
}

VisibleGameObject::VisibleGameObject(std::string filename)
	: _isLoaded(false)
{
	load(filename);
}

VisibleGameObject::~VisibleGameObject()
{
}

void VisibleGameObject::load(std::string filename) {
	if (_texture.loadFromFile(filename) == false) {
		_filename = "";
		_isLoaded = false;
	}
	else {
		_filename = filename;
		_sprite.setTexture(_texture);
		_isLoaded = true;
	}
}

void VisibleGameObject::draw(sf::RenderWindow& renderWindow)
{
	if (_isLoaded) {
		renderWindow.draw(_sprite);
	}
}

void VisibleGameObject::update(sf::Time elapsedTime)
{
}

void VisibleGameObject::setPosition(float x, float y) {
	if (_isLoaded) {
		_sprite.setPosition(x, y);
	}
}

sf::Vector2f VisibleGameObject::getPosition() const
{
	if (_isLoaded) {
		return _sprite.getPosition();
	}
	return sf::Vector2f();
}

sf::Sprite& VisibleGameObject::getSprite()
{
	return _sprite;
}

float VisibleGameObject::getWidth() const
{
	return _sprite.getLocalBounds().width;
}

float VisibleGameObject::getHeight() const
{
	return _sprite.getLocalBounds().height;
}

std::string VisibleGameObject::getName() const
{
	return _name;
}

void VisibleGameObject::setName(std::string name)
{
	_name = name;
}

sf::Rect<float> VisibleGameObject::getBoundingRect() const
{
	return _sprite.getGlobalBounds();
}

bool VisibleGameObject::isLoaded() const
{
	return _isLoaded;
}
