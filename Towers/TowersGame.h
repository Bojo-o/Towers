///////////////////////////////////////////////////////////
///// Towers! game 
///// 
///// Main game header, which commanding and processing all games parts
///////////////////////////////////////////////////////////

#pragma once

// headers
#include <SFML/Graphics.hpp>
#include "World.h"
#include "Selector.h"
#include "UI.h"


/**
	Main object of game Towers, commanding and processing all games parts
*/
class TowersGame {
public:
	// constructor, takes size of window, grid size of one game block space and speed of moving game screen location
	TowersGame(const unsigned xWinSize, const unsigned yWinSize, const float viewSpeed);
	// void method, takes two names of player and set up them
	void setPlayerNames(const std::string& playerOneName, const std::string& playerTwoName);
	// after succesfully loading, this start main game loop
	void launchGame();
private:
	enum class StateOfGame { PlayerOneMove, PlayerTwoMove, GameRound, EndOfGame};
	const unsigned GridSize = 64;
	StateOfGame CurrentState;
	Player* CurrentPlayer;
	Selector MapSelector;
	WorldMap Map;
	Player PlayerOne;
	Player PlayerTwo;
	GUI GameUI;
	sf::RenderWindow Window;
	sf::View View;
	sf::Time GameTimer;
	sf::Time LastGameTick;
	sf::Time LastSpawnTick;
	sf::Time SpawnSpeedValue;
	sf::Clock DeltaClock;
	sf::Clock GameClock;
	sf::Vector2i MouseWindowPosition;
	sf::Vector2f MouseViewPosition;
	sf::Vector2<std::size_t> MouseGridPosition;
	float ViewSpeedValue;
	float DeltaTime;
	// process time, which means spawn of monsters and update game elements
	void processGameTick();
	// process Mouse inputs, set up all Mouses positions
	void processMouseInput();
	// process Keyboard inputs, set up new region of view when "WASD" was pressed
	void processKeyboardInput();
	// for all towers in game, it resets their cooldown
	void resetTowersCooldown();
	// for all towers in game, it draw around them range circe
	void drawTowersRangeCircle();
	// for all towers, spawn and alive monsters, it process their bounds, as argument it takes players(attacker and defender), who store data about towers and monsters
	void processGameObjectsBounds(Player& attacker, Player& defender);
	// process for player his available space, where he can click 
	void processPlayerstAccessBound(const float min, const float max);
	// it close main game window and open new with error massage
	void launchErrorWindow(const std::string& errorTextMassage);
};