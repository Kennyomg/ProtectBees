#pragma once
#include "../VisibleGameObject.h"

// Extend VisibleGameObject
class WorkerBee : public VisibleGameObject
{
public:
	WorkerBee();
	virtual ~WorkerBee();
	void update(sf::Time deltaTime);

private:
	float _speed;
};