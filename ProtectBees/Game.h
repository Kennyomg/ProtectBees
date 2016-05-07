#pragma once
#include "Managers/GameObjectManager.h"
#include "Managers/AudioManager.h"
#include "layers/GUI.h"
#include "layers/PauseUI.h"

class Game
{

public:
	/*
	 * GameState represent each state the game can be in
	 * Depending on which state the game is in, a different screen will be shown
	 */
	enum GameState {
		Uninitialized, ShowingSplash, ShowingScore, Paused,
		ShowingMenu, Playing, Exiting
	};

	/*
	 * Start should only be called once in the int main() function
	 */
	static void start();

	/*
	 * GetWindow return a reference of the main window
	 * This can be used for eventpolling within different classes
	 */
	static sf::RenderWindow& getWindow();

	/*
	 * Returns the GameObjectManager
	 * This can be used for getting specific game object pointer
	 * Also usefull when you need the count of certain objects
	 */
	static GameObjectManager& getGameObjectManager();

	/*
	 * Returns the AudioManager
	 */
	static AudioManager& getAudioManager();

	/*
	 * Returns the deltaTime
	 */
	static sf::Time& getDeltaTime();

	/*
	 * Resets the deltaTime
	 * Since the menus are blocking functions till they return an action
	 * The deltaTime would get really high, so when the rest of the gameloop finishes
	 * Then it could be using for 1 frame a deltaTime which is to high, which results in a bear with a headstart
	 */
	static void resetDeltaTime();

	/*
	 * Get current level
	 */
	static int getLevel();

	/*
	 * Set level
	 */
	static void setLevel(int level);

	/*
	 * Get current gamestate
	 */
	static GameState getGameState();

	/*
	 * Set gamestate
	 */
	static void setGameState(GameState gameState);

	/*
	 * Reset gameobject in the level to default
	 */
	static void resetLevel();

	/*
	 * Define screen width and height
	 */
	const static int SCREEN_WIDTH = 800;
	const static int SCREEN_HEIGHT = 450;

private:
	
	/*
	 * Function for exiting the game
	 */
	static bool isExiting();

	/*
	 * Main game loop
	 */
	static void gameLoop();

	/*
	 * Show splash screen
	 */
	static void showSplashScreen();
	
	/*
	 * Show score screen
	 */
	static void showScoreScreen();
	
	/*
	 * Show main menu screen
	 */
	static void showMenu();

	/*
	 * Define clocks for fps and deltaTime
	 */
	static sf::Clock _clock;
	static sf::Clock _time;

	/*
	 * Define properties
	 */
	static GameState _gameState;
	static sf::RenderWindow _mainWindow;
	static sf::Time _deltaTime;
	static GUI _gui;
	static PauseUI _pauseUI;
	static int _level;
	static int _beeNameIndex;

	static bool _shiftKeyDown;
	static bool _ctrlKeyDown;
	static unsigned int _multiplier;

	static GameObjectManager _gameObjectManager;
	static AudioManager _audioManager;
};
