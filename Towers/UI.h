///////////////////////////////////////////////////////////
///// Towers! game - Game UI , processing wishes of players, who want building ,selling ...
/////			GUI work with Towers Buttons and Spaces , where Players try to click
/////				GUI has three states:
/////					- For building new Tower
/////					- For existing tower show sell and upgrade posibilities
/////					- For buying monsters to Player Army
///////////////////////////////////////////////////////////

#pragma once

// headers
#include "World.h"
#include "Selector.h"
#include "Buttons.h"
#include "SfmlShapes.h"
#include "SfmlText.h"

// define alias
class AbstractButton;
class AbstractTowerButton;
using ButtonTowers = std::unique_ptr<AbstractTowerButton>;
class AbstractActionButton;
using ButtonActions = std::unique_ptr<AbstractActionButton>;
class AbstractMonsterButton;
using ButtonMonsters = std::unique_ptr<AbstractMonsterButton>;

class GUIType;

// GUI request from clicked spaces

// Request for openning GUI menu for building towers
struct TowerGUI
{
	TowerGUI(sf::Vector2<std::size_t>& value) { TowerPosition = value;  }
	sf::Vector2<std::size_t> TowerPosition;
};
// Request for openning GUI menu for buying monsters
struct MonsterGUI
{
	MonsterGUI() {}
};
// Request for openning GUI menu for action as upgrading and selling
struct ActionGUI
{
	ActionGUI(sf::Vector2<std::size_t>& value, TowerStats* stats) { towerPosition = value; Stats = stats;
	}
	sf::Vector2<std::size_t> towerPosition;
	TowerStats* Stats;
};
// Button , that has area and function of clicking on him
class RectButton {
public:
	void setProperties(const sf::Vector2f& position, const sf::Vector2f& size) {
		ShapeCreator::rectangleShape(Shape, position, size,false,1.f,sf::Color::Black,sf::Color::Transparent);
		ShapeCreator::floatRect(Rect, position, size);
	}
	bool contains(const sf::Vector2f& mousePos) {
		return Rect.contains(mousePos);
	}
	void draw(sf::RenderWindow& window , bool renderNumbers) {
		window.draw(Shape);	
		if (Number > 0 && renderNumbers)
		{
			sf::Vector2f position(Shape.getPosition().x + 2, Shape.getPosition().y + Shape.getSize().y - 20);
			TextCreator::drawText(window, to_string(Number), position, sf::Color::Red);
		}
		
	}	
	void resetNumber() { Number = 0; }
	void increaseNumber() { Number++; }
private:
	sf::RectangleShape Shape;
	sf::FloatRect Rect;
	unsigned Number = 0;
};
// GUI for game Towers , process requests , shows menus and controls selections of what player want to do
class GUI {
public:
	GUI() { State = GUIType::Close; }
	// set GUI properties such as size ..
	void setGUIProperties(sf::RenderWindow& window);
	// render Players Bar
	void renderPlayerMenuBar(sf::RenderWindow& window, sf::View& view, Player& one, Player& two, Player* curPlayer);
	// render Menu
	void renderGameMenuForActions(sf::RenderWindow& window);
	// register all buttons
	void initializeButtons(const unsigned& gridSize, Textures& textures);
	// process mouse hover
	void hover(sf::RenderWindow& window, const sf::Vector2i& mousePos, WorldMap& map);
	// process click
	void clicked(const sf::Vector2i& mousePos,Player* currentPlayer,WorldMap& map);
	bool isOpen() { return State != GUIType::Close; }
	// start GUI wth Tower request, after clicked on free space
	void OpenGUI(TowerGUI info) {
		State = GUIType::ForTowers;
		PositionOfClickedParcel = info.TowerPosition;		
	}
	// start GUI wth Action request, after clicked on existing tower
	void OpenGUI(ActionGUI info) {
		State = GUIType::ForAction;
		PositionOfClickedParcel = info.towerPosition;
		TowerStatsForClickedTower = info.Stats;
	}
	// start GUI wth Monster request, after clicked on starting space , where units will be spawn
	void OpenGUI(MonsterGUI info) {
		State = GUIType::ForMonsters;
	}
	// close GIU
	void Close() { State = GUIType::Close; }
	// incraese number 
	void increaseNumberAtButton() {
		ClickedRectButton->increaseNumber();
	}
	// reset all number buttons
	void resetNumberButtons();
private:
	// draw all buttons for current state of GIU request
	template <typename T>
	void drawAllButtons(sf::RenderWindow& window, std::vector<T>& vector ) {
		for (auto&& x: vector)
		{
			x->draw(window);
		}
	}
	// func for helping calculate
	sf::Vector2f calculatePositionForButton(const std::size_t index) {
		auto y = index / 4;
		auto x = index % 4;
		return sf::Vector2f(TopLeftPosition.x + (static_cast<float>(x) * ButtonsSize.x),
							TopLeftPosition.y + (static_cast<float>(y) * ButtonsSize.y));
	}
	// template method for creating towers buttons 
	template <typename T>
	void AddNewButtonTowers(const unsigned price, const std::string name,const std::string desc, Textures& textures, const unsigned& gridSize, TowerStats stats) {
		sf::Vector2f buttonPos(calculatePositionForButton(TowersButtons.size()));
		TowersButtons.push_back(std::make_unique<T>(Base,buttonPos,ButtonsSize, name, price, desc, textures, gridSize, stats));
	}
	// template method for creating monsters buttons 
	template <typename T>
	void AddNewButtonMonster(const unsigned price, const std::string name,const std::string desc, Textures& textures, const unsigned& gridSize, MonsterStats stats) {
		sf::Vector2f buttonPos(calculatePositionForButton(MonstersButtons.size()));
		MonstersButtons.push_back(std::make_unique<T>(Base, buttonPos,ButtonsSize, name, price, desc, textures, gridSize, stats));		
	}
	// template method for creating actions buttons 
	template <typename T>
	void AddNewButtonAction(Textures& textures) {
		sf::Vector2f buttonPos(calculatePositionForButton(ActionsButtons.size()));
		ActionsButtons.push_back(std::make_unique<T>(buttonPos,ButtonsSize, textures));
	}
	enum class GUIType {
		ForMonsters,
		ForTowers,
		ForAction,
		Close
	};
	sf::Vector2<std::size_t> PositionOfClickedParcel;
	TowerStats* TowerStatsForClickedTower = nullptr;
	RectButton* ClickedRectButton = nullptr;
	GUIType State;
	AbstractButton* process(const std::size_t index);
	bool whichButton(std::size_t& index, const sf::Vector2f& mousePos);
	sf::Vector2f TopLeftPosition;
	sf::Vector2f ButtonsSize;
	sf::RectangleShape VerticalLine;
	sf::RectangleShape HorizontLine;
	sf::RectangleShape PlayerLine;
	sf::RectangleShape Base;
	sf::RectangleShape PlayerBase;
	sf::RectangleShape TurnsBase;
	RectButton RectsButtons[8][4];
	std::vector<ButtonTowers> TowersButtons;
	std::vector<ButtonActions> ActionsButtons;
	std::vector<ButtonMonsters> MonstersButtons;
};
