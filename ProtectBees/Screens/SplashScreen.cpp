#include "../stdafx.h"
#include "SplashScreen.h"
#include "../Game.h"
#include "../GameObjects/Entities/Player.h"

void SplashScreen::show(sf::RenderWindow& window)
{
	sf::Event event;
	while (true) {
		Game::resetDeltaTime();
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::EventType::KeyPressed || event.type == sf::Event::EventType::MouseButtonPressed) {
				Game::setGameState(Game::GameState::ShowingMenu);
				return;
			}

			if (event.type == sf::Event::Closed) {
				Game::setGameState(Game::GameState::Exiting);
				return;
			}
		}


		window.clear(sf::Color::White);

		// Draw splashscreen image
		Game::getGameObjectManager().get("splashscreen")->draw(window);
		Player* player = dynamic_cast<Player*>(Game::getGameObjectManager().get("player"));
		player->update(sf::seconds(0.0f));
		
		// Draw mouse
		player->draw(window);
		window.display();
	}
}
