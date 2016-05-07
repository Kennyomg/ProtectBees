#include "../stdafx.h"
#include "PauseUI.h"
#include "../Game.h"

PauseUI::PauseUI(std::string filepath)
	: _isLoaded(false)
{
	if (_font.loadFromFile(filepath))
	{
		// Tutorial text. I don't like the lack of support for multi line string,
		// but I think it should be readable like this
		sf::Text* t1 = new sf::Text("\
Hello, welcome to my game!\n\
Before we start I'll explain the game.\n\n\
The goal of the game is to stop the bear from stealing your honey.\n\
To achieve this you will have to be clever,\n\
about how you distribute your worker and soldier bees.\n\
At the middle of the screen you see the amount of honey you've collected.\n\
You can use the honey to create bees and buy upgrades,\n\
to increase your honey production you can buy more worker bees.\n\
To chase the bear away you have to buy soldier bees.\n\
You start the first level with a hive size of 10,\n\
which means you can only have 10 bees out at the same time.\n\
So 'bee'careful to leave room for atleast 1 soldier bee.\n\
Have Fun!\n\n\
Press W to buy a Worker Bee for 10 honey\n\n\
Press S to buy a Soldier Bee for 30 honey\
", _font, 20u);
		t1->setColor(sf::Color::Black);
		_texts.insert(std::pair<std::string, sf::Text*>("t1", t1));

		sf::Text* t2 = new sf::Text("Press SPACE to start/pause", _font, 30);
		t2->setPosition(float(Game::SCREEN_WIDTH) / 2 - t2->getGlobalBounds().width / 2, float(Game::SCREEN_HEIGHT) - t2->getGlobalBounds().height - 10);
		t2->setColor(sf::Color::Black);
		_texts.insert(std::pair<std::string, sf::Text*>("t2", t2));

		_overlay.setSize(sf::Vector2f(float(Game::SCREEN_WIDTH), float(Game::SCREEN_HEIGHT)));
		_overlay.setFillColor(sf::Color(255, 255, 255, 150));
	}
}

// Delete texts
PauseUI::~PauseUI()
{
	std::for_each(_texts.begin(), _texts.end(), TextDeallocator());
}

void PauseUI::update(sf::Time& deltaTime)
{
}

// Draw PauseUI
void PauseUI::draw(sf::RenderWindow& window)
{
	window.draw(_overlay);
	std::map<std::string, sf::Text*>::const_iterator itr = _texts.begin();
	while (itr != _texts.end())
	{
		window.draw(*itr->second);
		itr++;
	}
}