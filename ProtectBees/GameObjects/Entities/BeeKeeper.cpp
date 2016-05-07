#include "../../stdafx.h"
#include "BeeKeeper.h"
#include "../../Game.h"

BeeKeeper::BeeKeeper(unsigned int hp)
	: _hp(hp), _speed(15.0f), _isDead(false)
{
	load("Resources/Textures/BeeKeeper.png");
	setPosition(float(Game::SCREEN_WIDTH), float(Game::SCREEN_HEIGHT) * 0.55f);
	getSprite().scale(0.2f, 0.2f);
	getSprite().setOrigin(getSprite().getGlobalBounds().width / 2, getSprite().getGlobalBounds().height / 2);
}

BeeKeeper::~BeeKeeper()
{
}

void BeeKeeper::update(sf::Time deltaTime)
{
	// Check if the gamestate is playing, so the beekeeper wont walk when the game is paused
	if (Game::getGameState() == Game::GameState::Playing)
	{
		// If dead, turnaround and run away beer!
		if (_isDead)
		{
			if (getSprite().getPosition().x >= Game::SCREEN_WIDTH) {
				die();
			}
			getSprite().move(_speed * deltaTime.asSeconds() * 5.0f, 0.0f);
		}
		else if (getSprite().getPosition().x <= 0)
		{
			Game::setGameState(Game::GameState::ShowingMenu);
		}
		else if (_nearbySoldierBees.size() == 0) // Only move when there are no bees around
		{
			getSprite().move(-_speed * deltaTime.asSeconds(), 0.0f);
		}
	}
}

// Get hp
unsigned int BeeKeeper::getHp() const
{
	return _hp;
}

// Add soldierbee to list of nearby bees
void BeeKeeper::addSoldier(std::string name)
{
	if (_nearbySoldierBees.find(name) == _nearbySoldierBees.end()) {
		_nearbySoldierBees.insert(name);
	}
}

// Remove bee from list
void BeeKeeper::removeSoldier(std::string name)
{
	_nearbySoldierBees.erase(name);
}

// Function for getting hit
void BeeKeeper::hit(unsigned int damage)
{
	if (damage >= _hp) {
		if (getSprite().getScale().x > 0 && _isDead == false)
		{
			getSprite().setScale(-getSprite().getScale().x, getSprite().getScale().y);
			_isDead = true;
		}
	}
	else
	{
		_hp -= damage;
	}
}

// When the beekeeper is dead, show score screen
void BeeKeeper::die()
{
	Game::setGameState(Game::GameState::ShowingScore);
}