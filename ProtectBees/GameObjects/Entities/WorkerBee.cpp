#include "../../stdafx.h"
#include "WorkerBee.h"
#include "../../Game.h"

WorkerBee::WorkerBee()
{
	// Load workerbee image
	load("Resources/Textures/WorkerBee.png");

	// Set the 0, 0 point of the sprite to the middle of the image.
	// That way it's easier rotating on the middle (not that that is being done in this game)
	getSprite().setOrigin(getHeight() / 2, getWidth() / 2);

	// Set seed for random number generator
	std::srand((unsigned int)std::time(NULL));
	_speed = float(std::rand() % 10 + 2);

	// Set random size
	float rScale = float(std::rand() % 10 + 5) / 100.0f;
	getSprite().scale(rScale, rScale);

	// Set random position
	setPosition(float(std::rand() % 300 + 130), float((Game::SCREEN_HEIGHT / 4) * 3));

	// Decides what way the bee will go at the start
	if (std::rand() % 2 == 0)
	{
		_speed = -_speed;
	}
	else
	{
		getSprite().scale(-1.0f, 1.0f);
	}
}

WorkerBee::~WorkerBee()
{
}

// Update workerbee, this moves the bee and checks if it needs to turn around
void WorkerBee::update(sf::Time deltaTime)
{
	if (getPosition().x < 130.0f && _speed < 0)
	{
		_speed = -_speed;
		getSprite().scale(-1.0f, 1.0f);
	}
	else if (getPosition().x > 400.0f && _speed > 0)
	{
		_speed = -_speed;
		getSprite().scale(-1.0f, 1.0f);
	}

	getSprite().move(_speed * deltaTime.asSeconds(), std::cos(getPosition().x) * 0.3f);
}