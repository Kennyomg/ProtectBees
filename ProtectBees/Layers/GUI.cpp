#include "../stdafx.h"
#include "GUI.h"
#include "../Game.h"
#include "../GameObjects/Entities/Player.h"

GUI::GUI(std::string filename)
	: _elapsedTime(0.0f)
{
	if (_font.loadFromFile(filename))
	{

		sf::Color darkBlue(100, 0, 160);

		sf::Text* score = new sf::Text();

		score->setFont(_font);
		score->setColor(darkBlue);
		score->setCharacterSize(24);
		score->setPosition(Game::SCREEN_WIDTH / 2 - score->getGlobalBounds().width / 2, 50.0f);

		addText("score", score);

		sf::Text* availableBees = new sf::Text();

		availableBees->setFont(_font);
		availableBees->setColor(darkBlue);
		availableBees->setCharacterSize(12);
		availableBees->setPosition(50.0f, 50.0f);

		addText("availablebees", availableBees);

		sf::Text* workerBees = new sf::Text();

		workerBees->setFont(_font);
		workerBees->setColor(darkBlue);
		workerBees->setCharacterSize(12);
		workerBees->setPosition(50.0f, 70.0f);

		addText("workerbees", workerBees);

		sf::Text* soldierBees = new sf::Text();

		soldierBees->setFont(_font);
		soldierBees->setColor(darkBlue);
		soldierBees->setCharacterSize(12);
		soldierBees->setPosition(50.0f, 90.0f);

		addText("soldierbees", soldierBees);

		_isLoaded = true;
	}
}

GUI::~GUI()
{
	std::for_each(_texts.begin(), _texts.end(), TextDeallocator());
}

void GUI::addText(std::string name, sf::Text* text)
{
	_texts.insert(std::pair<std::string, sf::Text*>(name, text));
}

void GUI::removeText(std::string name)
{
	std::map<std::string, sf::Text*>::iterator results = _texts.find(name);
	if (results != _texts.end()) {
		delete results->second;
		_texts.erase(results);
	}
}

sf::Text* GUI::getText(std::string name)
{
	std::map<std::string, sf::Text*>::iterator results = _texts.find(name);
	if (results == _texts.end()) {
		return NULL;
	}
	return results->second;

}

void GUI::resetTime()
{
	_elapsedTime = 0.0f;
}

void GUI::draw(sf::RenderWindow& window)
{
	std::map<std::string, sf::Text*>::iterator itr = _texts.begin();
	while (itr != _texts.end())
	{
		window.draw(*itr->second);
		itr++;
	}
}

void GUI::update(float deltaTime)
{
	_elapsedTime += deltaTime;
	getText("score")->setString(std::to_string(dynamic_cast<Player*>(Game::getGameObjectManager().get("player"))->getScore()));
	getText("availablebees")->setString("Hive size: " + std::to_string(dynamic_cast<Player*>(Game::getGameObjectManager().get("player"))->getAvailableBees()));
	getText("workerbees")->setString("# of Worker bees: " + std::to_string(Game::getGameObjectManager().getWorkerBeeCount()));
	getText("soldierbees")->setString("# of Soldier bees: " + std::to_string(Game::getGameObjectManager().getSoldierBeeCount()));
}
