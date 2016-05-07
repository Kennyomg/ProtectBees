#include "../stdafx.h"
#include "GameObjectManager.h"
#include "../Game.h"

GameObjectManager::GameObjectManager()
{
}

GameObjectManager::~GameObjectManager()
{
	// Delete all gameobjects when manager is deconstructed
	std::for_each(_gameObjects.begin(), _gameObjects.end(), GameObjectDeallocator());
	std::for_each(_workerBeeObjects.begin(), _workerBeeObjects.end(), WorkerBeeDeallocator());
	std::for_each(_soldierBeeObjects.begin(), _soldierBeeObjects.end(), SoldierBeeDeallocator());
}

// Add game object
void GameObjectManager::add(std::string name, VisibleGameObject* gameObject)
{
	gameObject->setName(name);
	_gameObjects.insert(std::pair<std::string, VisibleGameObject*>(name, gameObject));
}

// Add workerbee
void GameObjectManager::add(std::string name, WorkerBee* gameObject)
{
	gameObject->setName(name);
	_workerBeeObjects.insert(std::pair<std::string, WorkerBee*>(name, gameObject));
}

// Add soldierbee
void GameObjectManager::add(std::string name, SoldierBee* gameObject)
{
	gameObject->setName(name);
	_soldierBeeObjects.insert(std::pair<std::string, SoldierBee*>(name, gameObject));
}

// Remove game object
void GameObjectManager::remove(std::string name)
{
	std::map<std::string, VisibleGameObject*>::iterator results = _gameObjects.find(name);
	if (results != _gameObjects.end()) {
		delete results->second;
		_gameObjects.erase(results);
	}
}

// Remove workerbee
void GameObjectManager::removeWorkerBee(std::string name)
{
	std::map<std::string, WorkerBee*>::iterator results = _workerBeeObjects.find(name);
	if (results != _workerBeeObjects.end()) {
		delete results->second;
		_workerBeeObjects.erase(results);
	}
}

// Remove soldierbee
void GameObjectManager::removeSoldierBee(std::string name)
{
	std::map<std::string, SoldierBee*>::iterator results = _soldierBeeObjects.find(name);
	if (results != _soldierBeeObjects.end()) {
		delete results->second;
		_soldierBeeObjects.erase(results);
	}
}

// Get game object
VisibleGameObject* GameObjectManager::get(std::string name) const
{
	std::map<std::string, VisibleGameObject*>::const_iterator results = _gameObjects.find(name);
	if (results == _gameObjects.end()) {
		return NULL;
	}
	return results->second;
}

// Delete all bees
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

// Get object count
int GameObjectManager::getObjectCount() const
{
	return _gameObjects.size();
}

// Get workerbee count
int GameObjectManager::getWorkerBeeCount() const
{
	return _workerBeeObjects.size();
}

// Get soldierbee count
int GameObjectManager::getSoldierBeeCount() const
{
	return _soldierBeeObjects.size();
}

// Draw all game object -- currently not used since I needed more control on the render order
void GameObjectManager::drawAll(sf::RenderWindow& renderWindow)
{
	std::map<std::string, VisibleGameObject*>::const_iterator itr = _gameObjects.begin();
	while (itr != _gameObjects.end())
	{
		itr->second->draw(renderWindow);
		itr++;
	}
}

// Draw all workerbees
void GameObjectManager::drawAllWorkerBees(sf::RenderWindow& renderWindow)
{
	std::map<std::string, WorkerBee*>::const_iterator itr = _workerBeeObjects.begin();
	while (itr != _workerBeeObjects.end())
	{
		itr->second->draw(renderWindow);
		itr++;
	}
}

// Draw all soldierbees
void GameObjectManager::drawAllSoldierBees(sf::RenderWindow& renderWindow)
{
	std::map<std::string, SoldierBee*>::const_iterator itr = _soldierBeeObjects.begin();
	while (itr != _soldierBeeObjects.end())
	{
		itr->second->draw(renderWindow);
		itr++;
	}
}

// Update all game objects
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
		
		// If the soldierbee is dead delete it
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