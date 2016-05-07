#include "../stdafx.h"
#include "MainMenu.h"
#include "../Game.h"
#include "../GameObjects/Entities/Player.h"

MainMenu::MenuResult MainMenu::show(sf::RenderWindow& window) {
	sf::Font font;
	// Load font
	font.loadFromFile("Resources/Fonts/Camouflage.ttf");

	// Setup clickable regions
	sf::RectangleShape playButtonRect(sf::Vector2f(float(Game::SCREEN_WIDTH) / 2, 107.f));
	playButtonRect.setPosition(sf::Vector2f(0, Game::SCREEN_HEIGHT - 107.f));
	playButtonRect.setOutlineThickness(1.f);
	playButtonRect.setOutlineColor(sf::Color::White);

	sf::RectangleShape menuButtonRect(sf::Vector2f(float(Game::SCREEN_WIDTH) / 2, 107.f));
	menuButtonRect.setPosition(sf::Vector2f(float(Game::SCREEN_WIDTH) / 2, Game::SCREEN_HEIGHT - 107.f));
	menuButtonRect.setOutlineThickness(1.f);
	menuButtonRect.setOutlineColor(sf::Color::White);

	// Setup button texts
	sf::Text playButtonText("Start", font);
	playButtonText.setCharacterSize(40u);
	playButtonText.setColor(sf::Color::White);
	playButtonText.setPosition(sf::Vector2f(playButtonRect.getGlobalBounds().width / 2 - playButtonText.getGlobalBounds().width / 2.f, playButtonRect.getGlobalBounds().top + playButtonRect.getGlobalBounds().height / 2 - playButtonText.getGlobalBounds().height / 2));

	sf::Text menuButtonText("Exit", font);
	menuButtonText.setCharacterSize(40u);
	menuButtonText.setColor(sf::Color::White);
	menuButtonText.setPosition(sf::Vector2f(menuButtonRect.getGlobalBounds().left + menuButtonRect.getGlobalBounds().width / 2 - menuButtonText.getGlobalBounds().width / 2.f, menuButtonRect.getGlobalBounds().top + menuButtonRect.getGlobalBounds().height / 2 - menuButtonText.getGlobalBounds().height / 2));

	// Play menu item coordinates
	MenuItem playButton;
	playButton.text = playButtonText;
	playButton.rect = playButtonRect;
	playButton.action = MainMenu::MenuResult::Play;

	// Exit menu item coordinates
	MenuItem menuButton;
	menuButton.text = menuButtonText;
	menuButton.rect = menuButtonRect;
	menuButton.action = MainMenu::MenuResult::Exit;

	// Add the buttons
	_menuItems.push_back(playButton);
	_menuItems.push_back(menuButton);

	return getMenuResponse(window);
}

// On click function to determine what button has been clicked and what action should be return
MainMenu::MenuResult MainMenu::handleClick(int x, int y)
{
	std::list<MenuItem>::iterator it;

	for (it = _menuItems.begin(); it != _menuItems.end(); it++) {
		sf::FloatRect menuItemRect = it->rect.getGlobalBounds();

		if (menuItemRect.contains(sf::Vector2f(float(x), float(y)))) {
			return it->action;
		}
	}

	return MainMenu::MenuResult::Nothing;
}

MainMenu::MenuResult MainMenu::getMenuResponse(sf::RenderWindow& window)
{
	sf::Event menuEvent;
	Player* player = dynamic_cast<Player*>(Game::getGameObjectManager().get("player"));

	// While loop to wait till an action is returned from the menu
	while (true) {

		// Reset the delta time since the delta time would otherwise be way to high
		Game::resetDeltaTime();
		while(window.pollEvent(menuEvent))
		{
			if (menuEvent.type == sf::Event::MouseButtonPressed) {
				return handleClick(menuEvent.mouseButton.x, menuEvent.mouseButton.y);
			}
			if (menuEvent.type == sf::Event::Closed) {
				return MainMenu::MenuResult::Exit;
			}
		}
		player->update(sf::seconds(0.0f));

		window.clear(sf::Color::Black);

		std::list<MenuItem>::iterator it;
		
		// Render background
		Game::getGameObjectManager().get("background")->draw(window);
		Game::getGameObjectManager().get("foreground")->draw(window);

		// Render all buttons with highlight when mouse on hovering it
		for (it = _menuItems.begin(); it != _menuItems.end(); it++)
		{
			if (it->rect.getGlobalBounds().contains(player->getPosition())) {
				sf::Color color = sf::Color::Blue;
				color.a = sf::Uint8(125);
				it->rect.setFillColor(color);
			}
			else
			{
				sf::Color color = sf::Color::Black;
				color.a = sf::Uint8(125);
				it->rect.setFillColor(color);
			}

			window.draw(it->rect);
			window.draw(it->text);
		}

		// Draw the mouse
		player->draw(window);
		window.display();

	}
}
