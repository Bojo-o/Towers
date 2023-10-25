///////////////////////////////////////////////////////////
///// Towers! game
///////////////////////////////////////////////////////////

// headers
#include "UI.h"
#include "SfmlText.h"

// namespaces
using namespace sf;
using namespace std;

// implement GUI_H_

void GUI::setGUIProperties(RenderWindow& window) {
	ShapeCreator::rectangleShape(PlayerBase, Vector2f(0, 0), Vector2f(window.getSize().x * 1.f, window.getSize().y / 10.f),false, 2.f, Color::Cyan);
	ShapeCreator::rectangleShape(Base, Vector2f(window.getSize().x / 2.f, window.getSize().y / 2.f), Vector2f((window.getSize().x / 3.f) * 2.f, (window.getSize().y / 3.f) * 2.f),true,2.f);
	ShapeCreator::rectangleShape(TurnsBase,Vector2f(0, window.getSize().y - 60.f), Vector2f(window.getSize().x * 1.f, 60.f), false, 2.f);
	ShapeCreator::rectangleShape(VerticalLine, Vector2f(Base.getPosition().x, Base.getPosition().y - (Base.getSize().y / 2)), Vector2f(1.f, Base.getSize().y));
	ShapeCreator::rectangleShape(HorizontLine, Vector2f(Base.getPosition().x, Base.getPosition().y), Vector2f(Base.getSize().x / 2, 1.f));
	ShapeCreator::rectangleShape(PlayerLine, Vector2f((window.getSize().x / 2.f) - 1.f, 0.f), Vector2f(2.f, PlayerBase.getSize().y),false,2.f);
	TopLeftPosition = Vector2f(Base.getPosition().x * 1.f - (Base.getSize().x / 2.f), Base.getPosition().y - (Base.getSize().y / 2.f));
	ButtonsSize= Vector2f (Base.getSize().x / 8.f, Base.getSize().y / 8.f);
	for (size_t i = 0; i < 8; i++)
	{
		for (size_t j = 0; j < 4; j++)
		{
			RectsButtons[i][j].setProperties(Vector2f(TopLeftPosition.x + (ButtonsSize.x * j), TopLeftPosition.y + (ButtonsSize.y * i)),ButtonsSize);
		}
	}
}
void GUI::renderGameMenuForActions(sf::RenderWindow& window) {
	if (State!=GUIType::Close)
	{
		window.draw(Base);
		window.draw(HorizontLine);
		window.draw(VerticalLine);
		bool renderNumbers = false;
		switch (State)
		{
		case GUI::GUIType::ForMonsters:
			drawAllButtons<ButtonMonsters>(window,MonstersButtons);
			renderNumbers = true;
			break;
		case GUI::GUIType::ForTowers:
			drawAllButtons<ButtonTowers>(window, TowersButtons);
			break;
		case GUI::GUIType::ForAction:
			drawAllButtons<ButtonActions>(window, ActionsButtons);
			break;
		case GUI::GUIType::Close:
			break;
		default:
			break;
		}
		for (size_t i = 0; i < 8; i++)
		{
			for (size_t j = 0; j < 4; j++)
			{				
				RectsButtons[i][j].draw(window,renderNumbers);
			}
		}
	}
}
void GUI::renderPlayerMenuBar(RenderWindow& window, View& view, Player& one, Player& two, Player* curPlayer) {
	window.draw(PlayerBase);
	window.draw(PlayerLine);
	TextCreator::drawText(window, one.Name, Vector2f(10.f, 10.f), Color::Black, 20);
	TextCreator::drawText(window, two.Name, Vector2f(window.getSize().x / 2.f + 10.f, 10.f), Color::Black, 20);
	float size = window.getSize().x / 4.f;
	TextCreator::drawText(window, "Gold :" + to_string(one.getGoldProperty()), Vector2f(size, 10.f), Color::Black, 20);
	TextCreator::drawText(window, "Gold :" + to_string(two.getGoldProperty()), Vector2f(size * 3.f, 10.f), Color::Black, 20);
	one.drawHP(window, Vector2f(10.f,PlayerBase.getSize().y / 2.f), Vector2f((PlayerBase.getSize().x / 2.f) - 20.f, PlayerBase.getSize().y / 2.f - 10.f));
	two.drawHP(window, Vector2f(PlayerBase.getSize().x / 2.f + 10.f, PlayerBase.getSize().y / 2.f), Vector2f((PlayerBase.getSize().x / 2.f) - 20.f, PlayerBase.getSize().y / 2.f - 10.f));
	if (curPlayer != nullptr)
	{
		window.draw(TurnsBase);
		TextCreator::drawText(window,"On the move is " + curPlayer->Name, Vector2f(230.f,window.getSize().y - 50.f), Color::Black, 24);
	}
	
	
}
void GUI::initializeButtons(const unsigned& gridSize, Textures& textures) {
	AddNewButtonTowers<ArcherButton>(25, "ArcherTower", "Shoot one arrow on\nground enemy unit", textures, gridSize, TowerStats(125, 5, 2, 40, 20, 1.3f, 1.5f, 1.20f, 1.25f));
	AddNewButtonTowers<CanonButton>(50, "CanonTower", "Shoot one steel ball on \n ground enemy unit", textures, gridSize, TowerStats(100, 15, 5, 60, 40, 1.4f, 2.f, 1.25f, 1.5f));
	AddNewButtonTowers<TurretButton>(75, "TurretTower", "Shoot bullets on all ground \nenemy units in range", textures, gridSize, TowerStats(135, 10, 2, 90, 60, 1.5f, 1.25f, 1.35f, 1.75f));
	AddNewButtonTowers<AirButton>(150, "AirTower", "Shoot on one enemy air unit", textures, gridSize, TowerStats(145, 20, 3, 175, 120, 1.5f, 1.5f, 1.35f, 1.75f));
	AddNewButtonTowers<AirTurretButton>(300, "AirTurretTower", "Shoot bullets on all enemy air \nunits in range", textures, gridSize, TowerStats(130, 15, 3, 360, 275, 1.5f, 1.5f, 1.35f, 2.f));
	AddNewButtonTowers<IceButton>(35, "IceTower", "Slow ground enemy units", textures, gridSize, TowerStats(90, 45, 0, 50, 25, 1.75f, 1.15f, 1.f, 2.f));
	AddNewButtonTowers<WindButton>(175, "WindTower", "Slow air enemy units", textures, gridSize, TowerStats(110, 35, 0, 200, 160, 1.65f, 1.15f, 1.f, 1.75f));
	AddNewButtonTowers<FireButton>(45, "FireTower", "Gives burns damage to \nground units", textures, gridSize, TowerStats(100, 1, 1, 50, 30, 1.3f, 1.25f, 1.25f, 1.35f));
	AddNewButtonTowers<PoisonButton>(100, "PoisonTower", "Gives poison damage to \nground units", textures, gridSize, TowerStats(115, 2, 1.25f, 120, 85, 1.4f, 1.25f, 1.15f, 1.75f));
	AddNewButtonTowers<StormButton>(200, "StormTower", "Gives storm damage to air units", textures, gridSize, TowerStats(120, 10, 1.5f, 250, 180, 1.3f, 1.45f, 1.15f, 2.f));
	AddNewButtonTowers<ExplodeButton>(500, "ExplodeTower", "All units in range goes booom", textures, gridSize, TowerStats(120, 999, 30, 500, 450, 1.5f, 1.f, 1.25f, 1.45f));
	AddNewButtonAction<SellButton>(textures);
	AddNewButtonAction<UpgradeButton>(textures);
	AddNewButtonMonster<SpiderButton>(10, "Spider", "Cheapest ground monster", textures, gridSize, MonsterStats(15, 10, 1.25f, 10));
	AddNewButtonMonster<IceSpiderButton>(20, "Ice Spider", "Cheap ground monster \n50% Ice resistance", textures, gridSize, MonsterStats(15, 10, 1.25f, 15));
	AddNewButtonMonster<GhoulButton>(50, "Ghoul", "Ground monster\n70% Archer, 25% Canon resistance\nImunnity towards\nFire deals 30% more damage", textures, gridSize, MonsterStats(25, 12, 1.5f, 20));
	AddNewButtonMonster<BearButton>(75, "Bear", "Ground monster\n25 % Canon resistance\nImunnity towards Archer", textures, gridSize, MonsterStats(35, 15, 1.5f, 25));
	AddNewButtonMonster<IceBearButton>(80, "Ice Bear", "Ground monster\nbehave as Bear +\nImunnity towards Ice\nFire deals 50% more damage", textures, gridSize, MonsterStats(40, 15, 1.5f, 25));
	AddNewButtonMonster<DevilButton>(100, "Devil", "Ground monster\n 20% Archer,25% Canon resistance\nImunity towards Fire", textures, gridSize, MonsterStats(60, 20, 1.5, 30));
	AddNewButtonMonster<WerewolfButton>(120, "Werewolf", "Ground monster\n70% Ice resistance\n30% Archer, Turret resistance", textures, gridSize, MonsterStats(50, 18, 2, 40));
	AddNewButtonMonster<GolemButton>(250, "Golem", "Expensive ground monster\n25% Canon, Poison resistance\n70% Turret resistance\nImunnity towards Archer,Fire", textures, gridSize, MonsterStats(125, 20, 1, 80));
	AddNewButtonMonster<GargoyleButton>(100, "Gargoyle", "Cheapest Air monster", textures, gridSize, MonsterStats(80, 25, 1.5f, 65));
	AddNewButtonMonster<PterodactylButton>(130, "Pterodactyl", "Air monster\n40% Wind, 25% Air resistance", textures, gridSize, MonsterStats(100, 30, 1.75f, 80));
	AddNewButtonMonster<GhidorahButton>(180, "Ghidorah", "Air monster\n20% Wind resistance\nImunnity towards Storm", textures, gridSize, MonsterStats(120, 35, 1.5f, 100));
	AddNewButtonMonster<WyvernButton>(200, "Wyvern", "Air monster\n40% Wind, 25% Air,Storm resistance", textures, gridSize, MonsterStats(125, 35, 1.75f, 105));
	AddNewButtonMonster<DragonButton>(300, "Dragon", "Expensive air monster\n50% Wind, 50% Air resistance\n30% AirTurret resistance", textures, gridSize, MonsterStats(200, 40, 1.75f, 180));
}
bool GUI::whichButton(size_t& index, const sf::Vector2f& mousePos) {
	for (size_t i = 0; i < 8; i++)
	{
		for (size_t j = 0; j < 4; j++)
		{
			if (RectsButtons[i][j].contains(mousePos))
			{
				ClickedRectButton = &RectsButtons[i][j];
				index = (i * 4) + j;
				return true;
			}	
		}
	}
	return false;
}
AbstractButton* GUI::process(const std::size_t index) {
	switch (State)
	{
	case GUI::GUIType::ForMonsters:
		if (MonstersButtons.size() > index)
		{
			return MonstersButtons.at(index).get();
		}
		break;
	case GUI::GUIType::ForTowers:
		if (TowersButtons.size() > index)
		{
			return TowersButtons.at(index).get();
		}
		break;
	case GUI::GUIType::ForAction:
		if (ActionsButtons.size() > index)
		{
			return ActionsButtons.at(index).get();
		}
		break;
	case GUI::GUIType::Close:
		break;
	default:
		break;
	}
	return nullptr;
}
void GUI::hover(RenderWindow& window, const sf::Vector2i& mousePos, WorldMap& map) {
	size_t buttonIndex;
	Vector2f mousePosF(mousePos.x * 1.f, mousePos.y * 1.f);
	if (whichButton(buttonIndex, mousePosF))
	{
		AbstractButton* button = process(buttonIndex);
		if (button != nullptr)
		{
			button->cursorAtButton(*TowerStatsForClickedTower,Base,window,PositionOfClickedParcel,map);
		}
	}
}
void GUI::clicked(const sf::Vector2i& mousePos, Player* currentPlayer, WorldMap& map) {
	size_t buttonIndex;
	Vector2f mousePosF(mousePos.x * 1.f, mousePos.y * 1.f);
	if (whichButton(buttonIndex, mousePosF))
	{
		AbstractButton* button = process(buttonIndex);
		if (button != nullptr)
		{
			button->clickAtButton(*TowerStatsForClickedTower, PositionOfClickedParcel, map, currentPlayer, *this);
		}
	}
	else
	{
		State = GUIType::Close;
	}	
}

void GUI::resetNumberButtons()
{
	for (size_t i = 0; i < 8; i++)
	{
		for (size_t j = 0; j < 4; j++)
		{
			RectsButtons[i][j].resetNumber();
		}
	}
}
