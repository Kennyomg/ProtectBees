#pragma once
#include "../VisibleGameObject.h"

class Player : public VisibleGameObject
{
public:
	Player();
	virtual ~Player();

	void update(sf::Time deltaTime);

	unsigned int getScore();
	unsigned int getAvailableBees();
	void setScore(unsigned int number);
	void setAvailableBees(unsigned int number);
	void addScore(unsigned int score);
	void addAvailableBees(unsigned int number);
	void subtractScore(unsigned int score);
	void subtractAvailableBees(unsigned int number);

private:
	unsigned int _score;
	unsigned int _availableBees;
	float _timer;
};