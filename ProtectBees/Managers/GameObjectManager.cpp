#include "../stdafx.h"
#include "GameObjectManager.h"
#include "../Game.h"

GameObjectManager::GameObjectManager()
{

}

GameObjectManager::~GameObjectManager()
{
	std::for_each(_gameObjects.begin(), _gameObjects.end(), GameObjectDeallocator());
	std::for_each(_workerBeeObjects.begin(), _workerBeeObjects.end(), WorkerBeeDeallocator());
	std::for_each(_soldierBeeObjects.begin(), _soldierBeeObjects.end(), SoldierBeeDeallocator());
}

void GameObjectManager::add(std::string name, VisibleGameObject* gameObject)
{
	gameObject->setName(name);
	_gameObjects.insert(std::pair<std::string, VisibleGameObject*>(name, gameObject));
}

void GameObjectManager::add(std::string name, WorkerBee* gameObject)
{
	gameObject->setName(name);
	_workerBeeObjects.insert(std::pair<std::string, WorkerBee*>(name, gameObject));
}

void GameObjectManager::add(std::string name, SoldierBee* gameObject)
{
	gameObject->setName(name);
	_soldierBeeObjects.insert(std::pair<std::string, SoldierBee*>(name, gameObject));
}

void GameObjectManager::remove(std::string name)
{
	std::map<std::string, VisibleGameObject*>::iterator results = _gameObjects.find(name);
	if (results != _gameObjects.end()) {
		delete results->second;
		_gameObjects.erase(results);
	}
}

void GameObjectManager::removeWorkerBee(std::string name)
{
	std::map<std::string, WorkerBee*>::iterator results = _workerBeeObjects.find(name);
	if (results != _workerBeeObjects.end()) {
		delete results->second;
		_workerBeeObjects.erase(results);
	}
}

void GameObjectManager::removeSoldierBee(std::string name)
{
	std::map<std::string, SoldierBee*>::iterator results = _soldierBeeObjects.find(name);
	if (results != _soldierBeeObjects.end()) {
		delete results->second;
		_soldierBeeObjects.erase(results);
	}
}

VisibleGameObject* GameObjectManager::get(std::string name) const
{
	std::map<std::string, VisibleGameObject*>::const_iterator results = _gameObjects.find(name);
	if (results == _gameObjects.end()) {
		return NULL;
	}
	return results->second;
}

void GameObjectManager::clearBees()
{
	std::map<std::string, WorkerBee*>::const_iterator workerItr = _workerBeeObjects.begin();
	std::map<std::string, WorkerBee*>::const_iterator workerItrEnd = _workerBeeObjects.end();

	for (; workerItr != workerItrEnd; ) {
		delete workerItr->second;
		_workerBeeObjects.erase(workerItr++);
	}

	std::map<std::string, SoldierBee*>::const_iterator soldierItr = _soldierBeeObjects.begin();
	std::map<std::string, SoldierBee*>::const_iterator soldierItrEnd = _soldierBeeObjects.end();

	for (; soldierItr != soldierItrEnd; ) {
		delete soldierItr->second;
		_soldierBeeObjects.erase(soldierItr++);
	}
}

int GameObjectManager::getObjectCount() const
{
	return _gameObjects.size();
}

int GameObjectManager::getWorkerBeeCount() const
{
	return _workerBeeObjects.size();
}

int GameObjectManager::getSoldierBeeCount() const
{
	return _soldierBeeObjects.size();
}

void GameObjectManager::drawAll(sf::RenderWindow& renderWindow)
{
	std::map<std::string, VisibleGameObject*>::const_iterator itr = _gameObjects.begin();
	while (itr != _gameObjects.end())
	{
		itr->second->draw(renderWindow);
		itr++;
	}
}

void GameObjectManager::drawAllWorkerBees(sf::RenderWindow& renderWindow)
{
	std::map<std::string, WorkerBee*>::const_iterator itr = _workerBeeObjects.begin();
	while (itr != _workerBeeObjects.end())
	{
		itr->second->draw(renderWindow);
		itr++;
	}
}

void GameObjectManager::drawAllSoldierBees(sf::RenderWindow& renderWindow)
{
	std::map<std::string, SoldierBee*>::const_iterator itr = _soldierBeeObjects.begin();
	while (itr != _soldierBeeObjects.end())
	{
		itr->second->draw(renderWindow);
		itr++;
	}
}

void GameObjectManager::updateAll()
{
	sf::Time timeDelta = Game::getDeltaTime();

	std::map<std::string, VisibleGameObject*>::const_iterator objItr = _gameObjects.begin();
	while (objItr != _gameObjects.end()) {
		objItr->second->update(timeDelta);
		objItr++;
	}

	std::map<std::string, WorkerBee*>::const_iterator workerItr = _workerBeeObjects.begin();
	while (workerItr != _workerBeeObjects.end()) {
		workerItr->second->update(timeDelta);
		workerItr++;
	}

	std::map<std::string, SoldierBee*>::const_iterator soldierItr = _soldierBeeObjects.begin();
	std::map<std::string, SoldierBee*>::const_iterator soldierItrEnd = _soldierBeeObjects.end();

	for (; soldierItr != soldierItrEnd; ) {
		if (soldierItr->second->isDead())
		{
			delete soldierItr->second;
			/*
			 * After erasing an iterator that iterator is invalid, but the other iterators are still valid
			 * So you can use soldierItr++ inside of the erase function for this to work
			 */
			_soldierBeeObjects.erase(soldierItr++); 
		}
		else
		{
			soldierItr->second->update(timeDelta);
			++soldierItr;
		}
	}
}