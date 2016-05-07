#pragma once
#include "SFML/Window.hpp"
#include "SFML/Graphics.hpp"
#include <list>

class MainMenu
{
public:
	// All actions that can be returned from the menu
	enum MenuResult { Nothing, Exit, Play };

	// Define MenuItem/button struct
	struct MenuItem
	{
	public:
		sf::RectangleShape rect;
		sf::Text text;
		MenuResult action;
	};

	// Show function
	MenuResult show(sf::RenderWindow& window);

private:
	MenuResult getMenuResponse(sf::RenderWindow& window);
	MenuResult handleClick(int x, int y);
	std::list<MenuItem> _menuItems;
};