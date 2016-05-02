#include "../../stdafx.h"
#include "WorkerBee.h"
#include "../../Game.h"

WorkerBee::WorkerBee()
{
	load("Resources/Textures/WorkerBee.png");
	getSprite().setOrigin(getHeight() / 2, getWidth() / 2);
	std::srand((unsigned int)std::time(NULL));
	_speed = float(std::rand() % 10 + 2);

	float rScale = float(std::rand() % 10 + 5) / 100.0f;
	getSprite().scale(rScale, rScale);
	setPosition(float(std::rand() % 300 + 130), float((Game::SCREEN_HEIGHT / 4) * 3));

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