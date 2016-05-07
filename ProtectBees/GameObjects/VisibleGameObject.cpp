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

// Load texture
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

// Draw object
void VisibleGameObject::draw(sf::RenderWindow& renderWindow)
{
	if (_isLoaded) {
		renderWindow.draw(_sprite);
	}
}

void VisibleGameObject::update(sf::Time elapsedTime)
{
}

// Set position
void VisibleGameObject::setPosition(float x, float y) {
	if (_isLoaded) {
		_sprite.setPosition(x, y);
	}
}

// Get position
sf::Vector2f VisibleGameObject::getPosition() const
{
	if (_isLoaded) {
		return _sprite.getPosition();
	}
	return sf::Vector2f();
}

// Get sprite
sf::Sprite& VisibleGameObject::getSprite()
{
	return _sprite;
}

// Get width
float VisibleGameObject::getWidth() const
{
	return _sprite.getLocalBounds().width;
}

// Get height
float VisibleGameObject::getHeight() const
{
	return _sprite.getLocalBounds().height;
}

// Get name
std::string VisibleGameObject::getName() const
{
	return _name;
}

// Set name
void VisibleGameObject::setName(std::string name)
{
	_name = name;
}

// Get bounding rectangle
sf::Rect<float> VisibleGameObject::getBoundingRect() const
{
	// Global bounds gets the rectangle after translations and scaling
	return _sprite.getGlobalBounds();
}

// Check if loaded
bool VisibleGameObject::isLoaded() const
{
	return _isLoaded;
}
