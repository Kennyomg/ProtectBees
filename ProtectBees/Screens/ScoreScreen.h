#pragma once
#include "SFML/Window.hpp"
#include "SFML/Graphics.hpp"
#include <list>

class ScoreScreen
{
public:
	enum MenuResult {
		Nothing, Menu, Play, UpgradeHive
	};

	struct MenuItem
	{
	public:
		sf::RectangleShape rect;
		sf::Text text;
		MenuResult action;
	};

	MenuResult show(sf::RenderWindow& window);
private:
	MenuResult getMenuResponse(sf::RenderWindow& window);
	MenuResult handleClick(int x, int y);
	std::list<MenuItem> _menuItems;
	sf::VertexArray _vertices;

	bool _shiftKeyDown;
	bool _ctrlKeyDown;
	unsigned int _multiplier;
};