#include "stdafx.h"
#include "Game.h"
#include "Screens\SplashScreen.h"
#include "Screens\ScoreScreen.h"
#include "Screens\MainMenu.h"
#include "GameObjects\VisibleGameObject.h"
#include "GameObjects\Entities\WorkerBee.h"
#include "GameObjects\Entities\SoldierBee.h"
#include "GameObjects\Entities\BeeKeeper.h"
#include "GameObjects\Entities\Player.h"
#include "GameObjects\Entities\ParticleSystem.h"
#include "AudioObjects\AudioObject.h"

void Game::start(void)
{
	if (_gameState != Game::GameState::Uninitialized) {
		return;
	}

	/*
	 * Creating window and settings framerate limit
	 */
	_mainWindow.create(sf::VideoMode(Game::SCREEN_WIDTH, Game::SCREEN_HEIGHT, 32), "Protect the bees!?");

	_mainWindow.setFramerateLimit(60);
	_mainWindow.setMouseCursorVisible(false);

	/*
	 * Loading Audio files and setting them up
	 */
	AudioObject* audioObject = new AudioObject();

	audioObject->load("Resources/Audio/belldandy.wav");
	audioObject->setLoop(true);
	audioObject->setVolume(10.0f);

	_audioManager.add("playscene", audioObject);

	/*
	 * Loading textures and creating objects
	 */
	_gameObjectManager.add("splashscreen", new VisibleGameObject("Resources/Textures/Splashscreen.png"));
	_gameObjectManager.add("background", new VisibleGameObject("Resources/Textures/background.png"));
	_gameObjectManager.add("foreground", new VisibleGameObject("Resources/Textures/foreground.png"));
	_gameObjectManager.add("beekeeper", new BeeKeeper(10u));
	Player* player = new Player();
	_gameObjectManager.add("player", player);

	/*
	 * Setting GameState to ShowingSpash
	 */
	_gameState = Game::GameState::ShowingSplash;

	/*
	 * Creating clock and timer for calculating the delta time and frames per second
	 */

	float timer = 0;
	unsigned int frames = 0;

	while (!isExiting()) {
		resetDeltaTime();
		gameLoop();

		/*
		 * Add up the number of frame for 1 second, show the sum, reset counter and repeat
		 */
		frames++;
		if (_time.getElapsedTime().asMilliseconds() - timer > 1000.0f)
		{
			timer += 1000.0f;
			_mainWindow.setTitle(sf::String("Protect the bees!? - " + std::to_string(frames) + " fps"));
			frames = 0;
		}
	}

	_mainWindow.close();
}

/*
 * isExiting gives you the opportunity to delete or save stuff before exitting the program
 */
bool Game::isExiting()
{
	if (_gameState == Game::GameState::Exiting) {
		return true;
	} else {
		return false;
	}
}

/*
 * Getter for _mainWindow
 */
sf::RenderWindow& Game::getWindow()
{
	return _mainWindow;
}

/*
 * Getter for _gameObjectManager
 */
GameObjectManager& Game::getGameObjectManager()
{
	return _gameObjectManager;
}

/*
 * Getter for _audioManager
 */
AudioManager& Game::getAudioManager()
{
	return _audioManager;
}

/*
 * Getter for _deltaTime
 */
sf::Time& Game::getDeltaTime()
{
	return _deltaTime;
}

/*
 * Reset deltaTime. This is a function because some blocking while loops in the menu's
 */
void Game::resetDeltaTime()
{
	_deltaTime = _clock.restart();
}

/*
 * Getter for _level
 */
int Game::getLevel()
{
	return _level;
}

/*
 * Setter for _level
 */
void Game::setLevel(int level)
{
	_level = level;
}

/*
 * Reset level
 */
void Game::resetLevel()
{
	_gameObjectManager.remove("beekeeper");
	
	// Create new BeeKeeper and set hp
	_gameObjectManager.add("beekeeper", new BeeKeeper((unsigned int)_level * (unsigned int)_level));
	_gameObjectManager.clearBees();
	_beeNameIndex = 0;
	_gameObjectManager.add("firstbee", new WorkerBee());
	Player* player = dynamic_cast<Player*>(_gameObjectManager.get("player"));
}

/*
 * Getter for _gameState
 */
Game::GameState Game::getGameState()
{
	return _gameState;
}

/*
 * Setter for _gameState
 */
void Game::setGameState(Game::GameState gameState)
{
	_gameState = gameState;
}

/*
 * gameLoop() is executed in the while loop of Game::start()
 * This function checks the state of the game and executes the code to render said state
 */
void Game::gameLoop()
{
	sf::Event currentEvent;
	Player* player = dynamic_cast<Player*>(_gameObjectManager.get("player"));

	// Depending on the game state render the correct screen
	switch (_gameState) {
		case Game::GameState::ShowingMenu: {
			showMenu();
			break;
		}
		case Game::GameState::ShowingSplash:
		{
			showSplashScreen();
			break;
		}
		case Game::GameState::ShowingScore:
		{
			showScoreScreen();
			break;
		}
		case Game::GameState::Paused:
		{
			player->update(sf::seconds(0.0f));
			_mainWindow.clear(sf::Color(0, 0, 0));

			// Draw everything in the correct order
			_gameObjectManager.get("background")->draw(_mainWindow);
			_gameObjectManager.drawAllWorkerBees(_mainWindow);
			_gameObjectManager.get("foreground")->draw(_mainWindow);
			_gameObjectManager.get("beekeeper")->draw(_mainWindow);
			_gameObjectManager.drawAllSoldierBees(_mainWindow);
			_pauseUI.draw(_mainWindow);
			player->draw(_mainWindow);

			_mainWindow.display();

			// Poll the event and set gamestate to the correct state
			while (_mainWindow.pollEvent(currentEvent))
			{
				if (currentEvent.type == sf::Event::KeyPressed) {
					if (currentEvent.key.code == sf::Keyboard::Escape || currentEvent.key.code == sf::Keyboard::Space) {
						// Unpause
						_gameState = Game::GameState::Playing;
					}
				}

				if (currentEvent.type == sf::Event::Closed) {
					// Quit the game
					_gameState = Game::GameState::Exiting;
				}
			}
			break;
		}
		case Game::GameState::Playing: {
			// Play music
			_audioManager.play("playscene");

			// Update all game objects
			_gameObjectManager.updateAll();

			// Update the graphical user interface
			_gui.update(_deltaTime);

			// Clear screen
			_mainWindow.clear(sf::Color(0, 0, 0));

			// Draw all game objects in this order into the screen buffer
			_gameObjectManager.get("background")->draw(_mainWindow);
			_gameObjectManager.drawAllWorkerBees(_mainWindow);
			_gameObjectManager.get("foreground")->draw(_mainWindow);
			_gameObjectManager.get("beekeeper")->draw(_mainWindow);
			_gameObjectManager.drawAllSoldierBees(_mainWindow);
			_gui.draw(_mainWindow);
			player->draw(_mainWindow);

			// Display the new screen buffer
			_mainWindow.display();

			// Check for events
			while (_mainWindow.pollEvent(currentEvent))
			{
				if (currentEvent.type == sf::Event::KeyPressed) {
					if (currentEvent.key.code == sf::Keyboard::Escape || currentEvent.key.code == sf::Keyboard::Space) {
						// Pause music and open the pause screen
						_audioManager.pause("playscene");
						_gameState = Game::GameState::Paused;
					}

					// Set shiftKeyDown to set a multiplier
					if (!_shiftKeyDown && currentEvent.key.code == sf::Keyboard::LShift)
					{
						_shiftKeyDown = true;
						_multiplier *= 10u;
					}

					// Set ctrilKeyDown to set a multiplier
					if (!_ctrlKeyDown && currentEvent.key.code == sf::Keyboard::LControl)
					{
						_ctrlKeyDown = true;
						_multiplier *= 100u;
					}

					// Check if the player has any bees available
					if (
						((unsigned int)_gameObjectManager.getSoldierBeeCount() + 
						(unsigned int)_gameObjectManager.getWorkerBeeCount()) + 
						(1u * _multiplier) <= player->getAvailableBees()
					)
					{
						// Check if the player has enough score/honey to buy a workerbee. _multiplier is used to buy multiple bees at a time
						if (currentEvent.key.code == sf::Keyboard::W && player->getScore() >= 10u * _multiplier) {
							for (unsigned int i = 0; i < _multiplier; i++)
							{
								_gameObjectManager.add("workerbee" + std::to_string(_beeNameIndex++), new WorkerBee());
							}
							player->subtractScore(10u * _multiplier);
						}
						// Check if the player has enough score/honey to buy a soldierbee. _multiplier is used to buy multiple bees at a time
						if (currentEvent.key.code == sf::Keyboard::S && player->getScore() >= 30u * _multiplier) {
							for (unsigned int i = 0; i < _multiplier; i++)
							{
								_gameObjectManager.add("soldierbee" + std::to_string(_beeNameIndex++), new SoldierBee());
							}
							player->subtractScore(30u * _multiplier);
						}
					}
				}

				if (currentEvent.type == sf::Event::KeyReleased)
				{
					// On release set the keyDown booleans to false and divide the multiplier again
					if (currentEvent.key.code == sf::Keyboard::LShift && _shiftKeyDown)
					{
						_shiftKeyDown = false;
						_multiplier /= 10u;
					}

					if (currentEvent.key.code == sf::Keyboard::LControl && _ctrlKeyDown)
					{
						_ctrlKeyDown = false;
						_multiplier /= 100u;
					}
				}

				// Exit on close event
				if (currentEvent.type == sf::Event::Closed) {
					_gameState = Game::GameState::Exiting;
				}
			}

			break;
		}
	}
}

// Create and show splashScreen
void Game::showSplashScreen()
{
	SplashScreen splashScreen;
	splashScreen.show(_mainWindow);
}

// Create and show scoreScreen
void Game::showScoreScreen()
{
	ScoreScreen scoreScreen;
	// This function is blocking and will wait for a result
	ScoreScreen::MenuResult result = scoreScreen.show(_mainWindow);
	switch (result)
	{
	case ScoreScreen::MenuResult::Menu:
		_gameState = Game::GameState::ShowingMenu;
		break;
	case ScoreScreen::MenuResult::Play:
		// Increase the level and reset the objects
		_level++;
		resetLevel();
		_gameState = Game::GameState::Playing;
		break;
	}
}

void Game::showMenu()
{
	MainMenu mainMenu;
	// This function is blocking and will wait for a result
	MainMenu::MenuResult result = mainMenu.show(_mainWindow);
	switch (result)
	{
	case MainMenu::MenuResult::Exit:
		_gameState = Game::GameState::Exiting;
		break;
	case MainMenu::MenuResult::Play:
		// Set the player stats to default and reset the level
		Player* player = dynamic_cast<Player*>(_gameObjectManager.get("player"));
		_level = 1;
		resetLevel();
		player->setScore(0u);
		player->setAvailableBees(10u);
		_gameState = Game::GameState::Paused;
		break;
	}
}

// Initialization of static class can't be done in a constructor since there will never be an instance
Game::GameState Game::_gameState = Game::GameState::Uninitialized;
sf::RenderWindow Game::_mainWindow;
sf::Time Game::_deltaTime;
GUI Game::_gui("Resources/Fonts/Camouflage.ttf");
PauseUI Game::_pauseUI("Resources/Fonts/Camouflage.ttf");
GameObjectManager Game::_gameObjectManager;
AudioManager Game::_audioManager;
sf::Clock Game::_clock;
sf::Clock Game::_time;

int Game::_level = 0;
int Game::_beeNameIndex = 0;

bool Game::_shiftKeyDown = false;
bool Game::_ctrlKeyDown = false;
unsigned int Game::_multiplier = 1u;