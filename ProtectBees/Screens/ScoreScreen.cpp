#include "../stdafx.h"
#include "ScoreScreen.h"
#include "../Game.h"
#include "../GameObjects/Entities/Player.h"

ScoreScreen::MenuResult ScoreScreen::show(sf::RenderWindow& window)
{
	_shiftKeyDown = false;
	_ctrlKeyDown = false;
	_multiplier = 1u;

	// Setting primitive type to quads will draw after every 4 vertices a rectangle
	_vertices.setPrimitiveType(sf::Quads);
	
	// Draw screen header
	_vertices.append(sf::Vertex(sf::Vector2f(0.f, 0.f), sf::Color::Blue, sf::Vector2f(0.f, 0.f)));
	_vertices.append(sf::Vertex(sf::Vector2f(float(Game::SCREEN_WIDTH), 0.f), sf::Color::White, sf::Vector2f(0.f, 10.f)));
	_vertices.append(sf::Vertex(sf::Vector2f(float(Game::SCREEN_WIDTH), 84.f), sf::Color::White, sf::Vector2f(10.f, 10.f)));
	_vertices.append(sf::Vertex(sf::Vector2f(0.f, 84.f), sf::Color::Blue, sf::Vector2f(10.f, 0.f)));

	Player* player = dynamic_cast<Player*>(Game::getGameObjectManager().get("player"));
	sf::Font font;
	
	// Load font
	font.loadFromFile("Resources/Fonts/Camouflage.ttf");

	// Set header text to amount of collected honey
	sf::Text scoreText("Collected honey: " + std::to_string(player->getScore()), font);
	scoreText.setCharacterSize(40u);
	scoreText.setColor(sf::Color::White);
	scoreText.setPosition(sf::Vector2f(float(Game::SCREEN_WIDTH) / 2.f - scoreText.getGlobalBounds().width / 2.f, 20.f));

	// Setup upgrade button
	sf::RectangleShape upgradeHiveButtonRect(sf::Vector2f(float(Game::SCREEN_WIDTH), 50.f));
	upgradeHiveButtonRect.setPosition(sf::Vector2f(0.f, 100.f));

	sf::Text upgradeHiveButtonText("Upgrade hive by " + std::to_string(10u * _multiplier) + "  " + std::to_string(200u * _multiplier) + " honey", font);
	upgradeHiveButtonText.setCharacterSize(24u);
	upgradeHiveButtonText.setColor(sf::Color::White);
	upgradeHiveButtonText.setPosition(sf::Vector2f(70.f, upgradeHiveButtonRect.getGlobalBounds().top + upgradeHiveButtonRect.getGlobalBounds().height / 2 - upgradeHiveButtonText.getGlobalBounds().height / 2));
	
	// Setup clickable regions
	sf::RectangleShape playButtonRect(sf::Vector2f(float(Game::SCREEN_WIDTH) / 2, 107.f));
	playButtonRect.setPosition(sf::Vector2f(0, Game::SCREEN_HEIGHT - 107.f));
	playButtonRect.setOutlineThickness(1.f);
	playButtonRect.setOutlineColor(sf::Color::White);

	sf::RectangleShape menuButtonRect(sf::Vector2f(float(Game::SCREEN_WIDTH) / 2, 107.f));
	menuButtonRect.setPosition(sf::Vector2f(float(Game::SCREEN_WIDTH) / 2, Game::SCREEN_HEIGHT - 107.f));
	menuButtonRect.setOutlineThickness(1.f);
	menuButtonRect.setOutlineColor(sf::Color::White);

	// Set button texts
	sf::Text playButtonText("Next level", font);
	playButtonText.setCharacterSize(40u);
	playButtonText.setColor(sf::Color::White);
	playButtonText.setPosition(sf::Vector2f(playButtonRect.getGlobalBounds().width / 2 - playButtonText.getGlobalBounds().width / 2.f, playButtonRect.getGlobalBounds().top + playButtonRect.getGlobalBounds().height / 2 - playButtonText.getGlobalBounds().height / 2));

	sf::Text menuButtonText("Exit to menu", font);
	menuButtonText.setCharacterSize(40u);
	menuButtonText.setColor(sf::Color::White);
	menuButtonText.setPosition(sf::Vector2f(menuButtonRect.getGlobalBounds().left + menuButtonRect.getGlobalBounds().width / 2 - menuButtonText.getGlobalBounds().width / 2.f, menuButtonRect.getGlobalBounds().top + menuButtonRect.getGlobalBounds().height / 2 - menuButtonText.getGlobalBounds().height / 2));

	// Create the menu items
	MenuItem score;
	score.text = scoreText;
	score.rect = sf::RectangleShape();
	score.action = ScoreScreen::MenuResult::Nothing;

	MenuItem upgradeHiveButton;
	upgradeHiveButton.text = upgradeHiveButtonText;
	upgradeHiveButton.rect = upgradeHiveButtonRect;
	upgradeHiveButton.action = ScoreScreen::MenuResult::UpgradeHive;

	MenuItem playButton;
	playButton.text = playButtonText;
	playButton.rect = playButtonRect;
	playButton.action = ScoreScreen::MenuResult::Play;

	MenuItem menuButton;
	menuButton.text = menuButtonText;
	menuButton.rect = menuButtonRect;
	menuButton.action = ScoreScreen::MenuResult::Menu;

	// Add menu items
	_menuItems.push_back(score);
	_menuItems.push_back(upgradeHiveButton);
	_menuItems.push_back(playButton);
	_menuItems.push_back(menuButton);

	return getMenuResponse(window);
}

// On click function to determine what button has been clicked and what action should be return
ScoreScreen::MenuResult ScoreScreen::handleClick(int x, int y)
{
	std::list<MenuItem>::iterator it;

	for (it = _menuItems.begin(); it != _menuItems.end(); it++) {
		sf::FloatRect menuItemRect = it->rect.getGlobalBounds();

		if (menuItemRect.contains(sf::Vector2f(float(x), float(y)))) {
			return it->action;
		}
	}

	return ScoreScreen::MenuResult::Nothing;
}

ScoreScreen::MenuResult ScoreScreen::getMenuResponse(sf::RenderWindow& window)
{
	sf::Event menuEvent;
	Player* player = dynamic_cast<Player*>(Game::getGameObjectManager().get("player"));

	// While loop to wait till an action is returned from the menu
	while (true) {

		// Reset the delta time since the delta time would otherwise be way to high
		Game::resetDeltaTime();
		while (window.pollEvent(menuEvent))
		{
			if (menuEvent.type == sf::Event::MouseButtonPressed) {
				ScoreScreen::MenuResult action = handleClick(menuEvent.mouseButton.x, menuEvent.mouseButton.y);
				switch (action) {
				case MenuResult::Menu:
					return action;
				case MenuResult::Play:
					return action;
				case MenuResult::UpgradeHive:
					// But check if possible and buy upgrade times multiplier to buy multiple at a time
					if (player->getScore() >= 200u * _multiplier)
					{
						player->addAvailableBees(10u * _multiplier);
						player->subtractScore(200u * _multiplier);
					}
				}
			}

			if (menuEvent.type == sf::Event::KeyPressed) {
				if (menuEvent.key.code == sf::Keyboard::LShift && !_shiftKeyDown)
				{
					_shiftKeyDown = true;
					_multiplier *= 10u;
				}

				if (menuEvent.key.code == sf::Keyboard::LControl && !_ctrlKeyDown)
				{
					_ctrlKeyDown = true;
					_multiplier *= 100u;
				}
			}

			if (menuEvent.type == sf::Event::KeyReleased) {
				if (menuEvent.key.code == sf::Keyboard::LShift && _shiftKeyDown)
				{
					_shiftKeyDown = false;
					_multiplier /= 10u;
				}

				if (menuEvent.key.code == sf::Keyboard::LControl && _ctrlKeyDown)
				{
					_ctrlKeyDown = false;
					_multiplier /= 100u;
				}
			}

			if (menuEvent.type == sf::Event::Closed) {
				Game::setGameState(Game::GameState::Exiting);
				return ScoreScreen::MenuResult::Nothing;
			}
		}

		player->update(sf::seconds(0.0f));

		window.clear(sf::Color::Black);

		std::list<MenuItem>::iterator it;

		// Render background
		Game::getGameObjectManager().get("background")->draw(window);
		Game::getGameObjectManager().get("foreground")->draw(window);
		window.draw(_vertices);

		// Render all buttons with highlight when mouse on hovering it
		for (it = _menuItems.begin(); it != _menuItems.end(); it++)
		{
			// Update score incase an upgrade is bought
			if (it == _menuItems.begin())
			{
				it->text.setString("Collected honey: " + std::to_string(player->getScore()));
			}
			// Set upgrade price and buy amount when multiplier is applied
			if (it == ++_menuItems.begin())
			{
				it->text.setString("Upgrade hive by " + std::to_string(10u * _multiplier) + "  " + std::to_string(200u * _multiplier) + " honey");
			}
			// Button highlighting
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