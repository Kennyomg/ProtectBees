#pragma once
#include "../VisibleGameObject.h"

class BeeKeeper : public VisibleGameObject
{
public:
	BeeKeeper(unsigned int hp);
	virtual ~BeeKeeper();

	void update(sf::Time deltaTime);

	unsigned int getHp() const;
	void addSoldier(std::string name);
	void removeSoldier(std::string name);
	void hit(unsigned int damage);
	void die();

private:
	float _speed;
	unsigned int _hp;
	bool _isDead;
	std::set<std::string> _nearbySoldierBees;

};