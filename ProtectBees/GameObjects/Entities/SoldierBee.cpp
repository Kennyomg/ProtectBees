#include "../../stdafx.h"
#include "SoldierBee.h"
#include "BeeKeeper.h"
#include "../../Game.h"

SoldierBee::SoldierBee()
	: _speed(20.0f), _hp(2u), _damage(1u), _range(100.0f), _attackSpeed(2), _timer(0.0f), _isDead(false), _particles(200)
{
	load("Resources/Textures/WorkerBee.png");
	setPosition(100.0f, float(Game::SCREEN_HEIGHT / 2));
	getSprite().scale(0.3f, 0.3f);
}

SoldierBee::~SoldierBee()
{
}

bool SoldierBee::isDead()
{
	return _isDead;
}

void SoldierBee::update(sf::Time deltaTime)
{
	_particles.setEmitter(sf::Vector2f(getPosition().x + 31.0f, getPosition().y + 40.0f));
	_particles.update(deltaTime);

	if (std::abs(dynamic_cast<BeeKeeper*>(Game::getGameObjectManager().get("beekeeper"))->getPosition().x - getPosition().x) <= _range)
	{
		_timer += deltaTime.asSeconds();

		if (_timer >= _attackSpeed) {
			attack();
			_timer = 0.0f;
		}
	}
	else
	{
		getSprite().move(_speed * deltaTime.asSeconds(), std::cos(getPosition().x) * 0.3f);
	}
}

void SoldierBee::draw(sf::RenderWindow& window)
{
	window.draw(_particles);
	VisibleGameObject::draw(window);
}

void SoldierBee::attack()
{
	BeeKeeper* beekeeper = dynamic_cast<BeeKeeper*>(Game::getGameObjectManager().get("beekeeper"));
	beekeeper->addSoldier(getName());
	beekeeper->hit(_damage);
	if (_damage >= _hp)
	{
		die();
	}
	else
	{
		_hp -= _damage;
	}
}

void SoldierBee::die()
{
	dynamic_cast<BeeKeeper*>(Game::getGameObjectManager().get("beekeeper"))->removeSoldier(getName());
	_isDead = true;
}