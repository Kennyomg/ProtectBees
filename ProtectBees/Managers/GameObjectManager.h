#pragma once
#include "../GameObjects/VisibleGameObject.h"
#include "../GameObjects/Entities/WorkerBee.h"
#include "../GameObjects/Entities/SoldierBee.h"

class GameObjectManager
{
public:
	GameObjectManager();
	~GameObjectManager();

	void add(std::string name, VisibleGameObject* gameObject);
	void add(std::string name, WorkerBee* gameObject);
	void add(std::string name, SoldierBee* gameObject);

	void remove(std::string name);
	void removeWorkerBee(std::string name);
	void removeSoldierBee(std::string name);
	int getObjectCount() const;
	int getWorkerBeeCount() const;
	int getSoldierBeeCount() const;
	VisibleGameObject* get(std::string name) const;

	void clearBees();

	void drawAll(sf::RenderWindow& renderWindow);
	void drawAllWorkerBees(sf::RenderWindow& renderWindow);
	void drawAllSoldierBees(sf::RenderWindow& renderWindow);
	void updateAll();

private:
	std::map<std::string, VisibleGameObject*> _gameObjects;
	std::map<std::string, WorkerBee*> _workerBeeObjects;
	std::map<std::string, SoldierBee*> _soldierBeeObjects;

	struct GameObjectDeallocator
	{
		void operator()(const std::pair<std::string, VisibleGameObject* > & p) const {
			delete p.second;
		}
	};

	struct WorkerBeeDeallocator
	{
		void operator()(const std::pair<std::string, WorkerBee* > & p) const {
			delete p.second;
		}
	};

	struct SoldierBeeDeallocator
	{
		void operator()(const std::pair<std::string, SoldierBee* > & p) const {
			delete p.second;
		}
	};
};