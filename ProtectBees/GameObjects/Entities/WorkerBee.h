#pragma once
#include "../VisibleGameObject.h"

class WorkerBee : public VisibleGameObject
{
public:
	WorkerBee();
	virtual ~WorkerBee();
	void update(sf::Time deltaTime);

private:
	float _speed;
};