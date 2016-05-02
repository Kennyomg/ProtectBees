#include "../../stdafx.h"
#include "Player.h"
#include "../../Game.h"

Player::Player()
	: _score(0u), _availableBees(0u), _timer(0.0f)
{
	load("Resources/Textures/cursor.png");
	assert(isLoaded());
}

Player::~Player()
{

}

void Player::update(sf::Time deltaTime)
{
	getSprite().setPosition(float(sf::Mouse::getPosition(Game::getWindow()).x), float(sf::Mouse::getPosition(Game::getWindow()).y));

	_timer += deltaTime.asSeconds();
	if (_timer >= 1.0f)
	{
		addScore((unsigned int)Game::getGameObjectManager().getWorkerBeeCount());
		_timer = 0;
	}
}

unsigned int Player::getScore()
{
	return _score;
}

unsigned int Player::getAvailableBees()
{
	return _availableBees;
}

void Player::setScore(unsigned int score)
{
	_score = score;
}

void Player::setAvailableBees(unsigned int number)
{
	_availableBees = number;
}

void Player::addScore(unsigned int score)
{
	_score += score;
}

void Player::addAvailableBees(unsigned int number)
{
	_availableBees += number;
}

void Player::subtractScore(unsigned int score)
{
	if (_score >= score)
	{
		_score -= score;
	}
}

void Player::subtractAvailableBees(unsigned int number)
{
	if (_availableBees >= number)
	{
		_availableBees -= number;
	}
}