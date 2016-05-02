#pragma once
#include "../VisibleGameObject.h"
#include "ParticleSystem.h"

class SoldierBee : public VisibleGameObject
{
public:
	SoldierBee();
	virtual ~SoldierBee();
	bool isDead();
	void update(sf::Time deltaTime);
	void draw(sf::RenderWindow& window);
	void attack();
	void die();

private:
	float _speed;
	float _attackSpeed; // Attack interval in seconds (_attackSpeed of 2.0f means 1 attack every 2 seconds)
	float _range;
	float _timer;
	bool _isDead;
	unsigned int _hp;
	unsigned int _damage;
	ParticleSystem _particles;
};