///////////////////////////////////////////////////////////
///// Towers! game
///////////////////////////////////////////////////////////

// headers
#include "TowersGame.h"
#include "GameExceptions.h"
#include "SfmlText.h"

// namespaces
using namespace sf;
using namespace std;

// implement TowersGame_H_

TowersGame::TowersGame(const unsigned xWindowSize, const unsigned yWindowSize, const float viewSpeed) {
	try
	{
		// set up game window and view
		cout << "Creating game window.." << endl;
		float gridSizeF = static_cast<float>(GridSize);
		Window.create(VideoMode(xWindowSize, yWindowSize), "Towers", sf::Style::Close);
		Window.setFramerateLimit(60);
		View.setSize(static_cast<float>(xWindowSize), static_cast<float>(yWindowSize));
		View.setCenter(Window.getSize().x / 2.f, Window.getSize().y / 2.f);
		ViewSpeedValue = viewSpeed;
		// set up Selector
		MapSelector.SetSelector(Vector2f(gridSizeF, gridSizeF), Color::Blue, 1.f, Vector2f(0.f, 0.f));
		// set time
		cout << "Set up time.." << endl;
		DeltaTime = 0.f;
		LastGameTick = sf::seconds(0.f);
		LastSpawnTick = sf::seconds(0.f);
		SpawnSpeedValue = sf::seconds(2.f);
		// set game state
		CurrentState = StateOfGame::PlayerOneMove;
		CurrentPlayer = &PlayerOne;
		// set UI
		cout << "Initializing GUI..." << endl;
		GameUI.setGUIProperties(Window);
		// load texture and create map
		cout << "Loading textures..." << endl;
		Map.setTextures();
		Map.setGridSize(GridSize);
		cout << "Initializing world..." << endl;
		Map.createMap("MapData.txt", GridSize, PlayerOne, PlayerTwo);
		// set game buttons
		GameUI.initializeButtons(GridSize, Map.Textures);
		cout << "Launch..." << endl;
	}
	catch (FailLoadMap& e)
	{
		launchErrorWindow(e.what());
	}
	catch (...)
	{
		std::cerr << "unhandled exception";
	}
}
void TowersGame::setPlayerNames(const string& playerOneName, const string& playerTwoName) {
	PlayerOne.Name = playerOneName;
	PlayerTwo.Name = playerTwoName;
};
void TowersGame::processKeyboardInput() {
	if (GameUI.isOpen()) {return;}
	if (Keyboard::isKeyPressed(Keyboard::A))
	{
		View.move(-ViewSpeedValue * DeltaTime, 0.f);
	}
	if (Keyboard::isKeyPressed(Keyboard::D))
	{
		View.move(ViewSpeedValue * DeltaTime, 0.f);
	}
	if (Keyboard::isKeyPressed(Keyboard::W))
	{
		View.move(0.f, -ViewSpeedValue * DeltaTime);
	}
	if (Keyboard::isKeyPressed(Keyboard::S))
	{
		View.move(0.f, ViewSpeedValue * DeltaTime);
	}
}
void TowersGame::processPlayerstAccessBound(const float min, const float max) {
	if (MouseViewPosition.x >= min && MouseViewPosition.x <= max)
	{
		MouseGridPosition.x = static_cast<unsigned>(MouseViewPosition.x / Map.getGridFSize());
	}
	if (MouseViewPosition.y >= 0.f && MouseViewPosition.y <= Map.getMapSize().y * Map.getGridFSize())
	{
		MouseGridPosition.y = static_cast<unsigned>(MouseViewPosition.y / Map.getGridFSize());
	}
}
void TowersGame::processMouseInput() {
	MouseWindowPosition = Mouse::getPosition(Window);
	Window.setView(View);
	MouseViewPosition = Window.mapPixelToCoords(MouseWindowPosition);
	if (CurrentState == StateOfGame::PlayerOneMove)
	{
		processPlayerstAccessBound(0.f, (Map.getMapBound() + 1) * Map.getGridFSize());
	}
	if (CurrentState == StateOfGame::PlayerTwoMove)
	{
		processPlayerstAccessBound(Map.getMapBound() * Map.getGridFSize(), Map.getMapSize().x * Map.getGridFSize());
	}
	Window.setView(Window.getDefaultView());
	// update selector
	MapSelector.UpdateSelectorPosition(MouseGridPosition);
}
void TowersGame::launchErrorWindow(const string& errorTextMassage) {
	Window.close();
	RenderWindow ErrorWindow(VideoMode(400,150), "Error", sf::Style::Close);
	TextCreator::drawText(ErrorWindow, errorTextMassage, Vector2f(0.f,0.f), Color::White, 20);
	ErrorWindow.display();
	cout << "something went wrong";
	while (ErrorWindow.isOpen())
	{
		sf::Event event;
		while (ErrorWindow.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				ErrorWindow.close();
		}
	}
}
void TowersGame::resetTowersCooldown() {
	for (auto&& tower : PlayerOne.getTowerList())
	{
		tower->resetCooldown();
	}
	for (auto&& tower : PlayerTwo.getTowerList())
	{
		tower->resetCooldown();
	}
}
void TowersGame::processGameObjectsBounds(Player& attacker, Player& defender) {
	for (auto&& monster : attacker.getArmy())
	{
		monster.get()->setSpeedDeceleration(0);
	}
	for (auto&& tower : defender.getTowerList())
	{
		if (tower->hasTowerEfect()) // efect towers : Ice , fire , poison
		{
			if (tower->isCooldownZero(GameTimer))
			{
				for (auto&& monster : attacker.getArmy())
				{
					if (tower->isMonsterInRange(monster))
					{
						tower->attack(monster, GameTimer, attacker, defender);
					}
				}
			}
		}
		else // no efect tower : Archer
		{
			for (auto&& monster : attacker.getArmy())
			{
				if (tower->isMonsterInRange(monster))
				{
					if (tower->isCooldownZero(GameTimer))
					{
						tower->attack(monster, GameTimer, attacker, defender);
					}
				}
			}
		}
	}
}

void TowersGame::processGameTick() {
	GameTimer = GameClock.getElapsedTime();
	if (GameTimer - LastSpawnTick > SpawnSpeedValue)
	{
		LastSpawnTick = GameTimer;
		PlayerOne.getArmy().spawnMonster();
		PlayerTwo.getArmy().spawnMonster();
	}
	if (GameTimer - LastGameTick > milliseconds(1))
	{
		LastGameTick = GameTimer;
		this->processGameObjectsBounds(PlayerOne, PlayerTwo);
		this->processGameObjectsBounds(PlayerTwo, PlayerOne);
		PlayerOne.getArmy().moveArmy(PlayerOne, PlayerTwo);
		PlayerTwo.getArmy().moveArmy(PlayerTwo, PlayerOne);
		if (PlayerOne.getArmy().isArmyDead() && PlayerTwo.getArmy().isArmyDead())
		{
			this->resetTowersCooldown();
			// income		
			PlayerOne.getGold(PlayerOne.getTowerList().getSize() * 20);
			PlayerTwo.getGold(PlayerTwo.getTowerList().getSize() * 20);
			// clear army
			PlayerOne.getArmy().clearArmy();
			PlayerTwo.getArmy().clearArmy();				
			CurrentPlayer = &PlayerOne;
			CurrentState = StateOfGame::PlayerOneMove;
			View.zoom(0.5f);
		}
	}
}
void TowersGame::drawTowersRangeCircle() {
	for (auto&& tower : PlayerOne.getTowerList())
	{
		tower->drawRangeCircle(Window);
	}
	for (auto&& tower : PlayerTwo.getTowerList())
	{
		tower->drawRangeCircle(Window);
	}
}
void TowersGame::launchGame() {
	try
	{
		// main game loop
		while (Window.isOpen())
		{
			// check game end
			if (PlayerOne.getHpProperty() <= 0.f && PlayerTwo.getHpProperty() <= 0.f)
			{
				CurrentState = StateOfGame::EndOfGame;
				cout << "Tie " << endl;
			} else if (PlayerOne.getHpProperty() <= 0.f){
				CurrentState = StateOfGame::EndOfGame;
				cout << "Congratulations to the winner " << PlayerOne.Name << endl;
			} else if (PlayerTwo.getHpProperty() <= 0.f){
				CurrentState = StateOfGame::EndOfGame;
				cout << "Congratulations to the winner " << PlayerTwo.Name << endl;
			}
			if (CurrentState == StateOfGame::EndOfGame)
			{
				Window.close();
			}
			// update delta time
			DeltaTime = DeltaClock.restart().asSeconds();
			// update Mouse input
			this->processMouseInput();
			// update keyboard input
			this->processKeyboardInput();
			// process events
			sf::Event event;
			while (Window.pollEvent(event))
			{				
				if (event.type == sf::Event::Closed)
					Window.close();
				if (event.type == sf::Event::KeyPressed)
				{
					if (event.key.code == sf::Keyboard::Enter)
					{
						GameUI.Close();
						GameUI.resetNumberButtons();
						switch (CurrentState)
						{
						case StateOfGame::PlayerOneMove:
							CurrentState = StateOfGame::PlayerTwoMove;
							CurrentPlayer = &PlayerTwo;
							MouseGridPosition.x = Map.getMapBound() + 1;
							MouseGridPosition.y = 0;
							break;
						case StateOfGame::PlayerTwoMove:
							CurrentState = StateOfGame::GameRound;
							CurrentPlayer = nullptr;
							View.zoom(2);
							break;
						case StateOfGame::GameRound:
							MouseGridPosition.x = 0;
							MouseGridPosition.y = 0;
							break;
						case StateOfGame::EndOfGame:
							Window.close();
						default:
							break;
						}
					}
				}
				if (event.type == sf::Event::MouseButtonPressed && CurrentState != StateOfGame::GameRound)
					if (GameUI.isOpen())
					{
						GameUI.clicked(MouseWindowPosition , CurrentPlayer, Map);
					}
					else
					{
						Map.getParcelAt(MouseGridPosition)->click(GameUI);
					}
			}
			// update
			if (CurrentState == StateOfGame::GameRound)
			{
				this->processGameTick();
			}
			// render
			Window.clear();
			Window.setView(View);
			// render game objects			
			Map.drawMap(Window);
			if (CurrentState == StateOfGame::GameRound)
			{
				PlayerOne.getArmy().drawArmy(Window);
				PlayerTwo.getArmy().drawArmy(Window);
			}
			this->drawTowersRangeCircle();
			// if UI is open ignore:
			if (!GameUI.isOpen() && CurrentState != StateOfGame::GameRound)
			{
				MapSelector.draw(Window);
			}
			Window.setView(Window.getDefaultView());
			// render UI
			GameUI.renderPlayerMenuBar(Window, View, PlayerOne, PlayerTwo, CurrentPlayer);
			GameUI.renderGameMenuForActions(Window);
			GameUI.hover(Window, MouseWindowPosition, Map);
			//display all rendered object 
			Window.display();

		}
	}
	catch (FailLoadMap& e)
	{
		launchErrorWindow(e.what());
	}
	catch (...)
	{
		std::cerr << "unhandled exception";
	}
}