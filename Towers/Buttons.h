///////////////////////////////////////////////////////////
///// Towers! game - Buttons 
/////        button has three methods:
/////			cursorAtButton -> when is mouse cursor on button position, it process action,
/////				which render details about button as Towers Stats, Price of bying ... 
/////			clickAtButton -> after clicking on button, it process action, that button do
/////			draw -> draw on window button
///////////////////////////////////////////////////////////

#pragma once
// headers
#include "World.h"
#include "UI.h"

class GUI;

/**
	Abstact Button , behave as button in game menu
*/
class AbstractButton {
protected:
	sf::Sprite ButtonSprite;
public:
	// virtual, when is mouse cursor on button position, it render details
	virtual void cursorAtButton(TowerStats& stats, sf::RectangleShape& base, sf::RenderWindow& window, const sf::Vector2<std::size_t>& positionOfParcel, WorldMap& map) = 0;
	// virtual, after clicking on button, it process action
	virtual void clickAtButton(TowerStats& stats, const sf::Vector2<std::size_t>& positionOfParcel, WorldMap& map, Player* player, GUI& gui) = 0;
	// draw button on render window
	void draw(sf::RenderWindow& window);
};
/**
	Abstact Monster Button , behave as monster button in game menu , for buying monsters
*/
class AbstractMonsterButton : public  AbstractButton {
protected:
	unsigned PriceForAction = 0;
	sf::Sprite MonsterSprite;
	std::string Description;
	std::string Name;
	MonsterStats Stats;
public:
	void initialize(const std::string text, sf::RectangleShape& base, const sf::Vector2f buttonPos, const sf::Vector2f buttonSize, Textures& textures, const unsigned& gridSize);
	// generate monster text for details to show on window
	std::string generateMonsterStatsText();
	void cursorAtButton(TowerStats& stats, sf::RectangleShape& base, sf::RenderWindow& window, const sf::Vector2<std::size_t>& positionOfParcel, WorldMap& map) override;
};
// Spider
class SpiderButton : public AbstractMonsterButton {
public:
	SpiderButton(sf::RectangleShape& base, const sf::Vector2f buttonPos, const sf::Vector2f buttonSize, const std::string& name, const unsigned& price, const std::string& desc, Textures& textures, const unsigned& gridSize, MonsterStats& stats);
	void clickAtButton(TowerStats& stats, const sf::Vector2<std::size_t>& positionOfParcel, WorldMap& map, Player* player, GUI& gui) override;
};
// Ice Spider
class IceSpiderButton : public AbstractMonsterButton {
public:
	IceSpiderButton(sf::RectangleShape& base, const sf::Vector2f buttonPos, const sf::Vector2f buttonSize, const std::string& name, const unsigned& price, const std::string& desc, Textures& textures, const unsigned& gridSize, MonsterStats& stats);
	void clickAtButton(TowerStats& stats, const sf::Vector2<std::size_t>& positionOfParcel, WorldMap& map, Player* player, GUI& gui) override;
};
// Ghoul
class GhoulButton : public AbstractMonsterButton {
public:
	GhoulButton(sf::RectangleShape& base, const sf::Vector2f buttonPos, const sf::Vector2f buttonSize, const std::string& name, const unsigned& price, const std::string& desc, Textures& textures, const unsigned& gridSize, MonsterStats& stats);
	void clickAtButton(TowerStats& stats, const sf::Vector2<std::size_t>& positionOfParcel, WorldMap& map, Player* player, GUI& gui) override;
};
// Bear
class BearButton : public AbstractMonsterButton {
public:
	BearButton(sf::RectangleShape& base, const sf::Vector2f buttonPos, const sf::Vector2f buttonSize, const std::string& name, const unsigned& price, const std::string& desc, Textures& textures, const unsigned& gridSize, MonsterStats& stats);
	void clickAtButton(TowerStats& stats, const sf::Vector2<std::size_t>& positionOfParcel, WorldMap& map, Player* player, GUI& gui) override;
};
// Ice Bear
class IceBearButton : public AbstractMonsterButton {
public:
	IceBearButton(sf::RectangleShape& base, const sf::Vector2f buttonPos, const sf::Vector2f buttonSize, const std::string& name, const unsigned& price, const std::string& desc, Textures& textures, const unsigned& gridSize, MonsterStats& stats);
	void clickAtButton(TowerStats& stats, const sf::Vector2<std::size_t>& positionOfParcel, WorldMap& map, Player* player, GUI& gui) override;
};
// Devil
class DevilButton : public AbstractMonsterButton {
public:
	DevilButton(sf::RectangleShape& base, const sf::Vector2f buttonPos, const sf::Vector2f buttonSize, const std::string& name, const unsigned& price, const std::string& desc, Textures& textures, const unsigned& gridSize, MonsterStats& stats);
	void clickAtButton(TowerStats& stats, const sf::Vector2<std::size_t>& positionOfParcel, WorldMap& map, Player* player, GUI& gui) override;
};
// Werewolf
class WerewolfButton : public AbstractMonsterButton {
public:
	WerewolfButton(sf::RectangleShape& base, const sf::Vector2f buttonPos, const sf::Vector2f buttonSize, const std::string& name, const unsigned& price, const std::string& desc, Textures& textures, const unsigned& gridSize, MonsterStats& stats);
	void clickAtButton(TowerStats& stats, const sf::Vector2<std::size_t>& positionOfParcel, WorldMap& map, Player* player, GUI& gui) override;
};
// Golem
class GolemButton : public AbstractMonsterButton {
public:
	GolemButton(sf::RectangleShape& base, const sf::Vector2f buttonPos, const sf::Vector2f buttonSize, const std::string& name, const unsigned& price, const std::string& desc, Textures& textures, const unsigned& gridSize, MonsterStats& stats);
	void clickAtButton(TowerStats& stats, const sf::Vector2<std::size_t>& positionOfParcel, WorldMap& map, Player* player, GUI& gui) override;
};
// Gargoyle
class GargoyleButton : public AbstractMonsterButton {
public:
	GargoyleButton(sf::RectangleShape& base, const sf::Vector2f buttonPos, const sf::Vector2f buttonSize, const std::string& name, const unsigned& price, const std::string& desc, Textures& textures, const unsigned& gridSize, MonsterStats& stats);
	void clickAtButton(TowerStats& stats, const sf::Vector2<std::size_t>& positionOfParcel, WorldMap& map, Player* player, GUI& gui) override;
};
// Pterodactyl
class PterodactylButton : public AbstractMonsterButton {
public:
	PterodactylButton(sf::RectangleShape& base, const sf::Vector2f buttonPos, const sf::Vector2f buttonSize, const std::string& name, const unsigned& price, const std::string& desc, Textures& textures, const unsigned& gridSize, MonsterStats& stats);
	void clickAtButton(TowerStats& stats, const sf::Vector2<std::size_t>& positionOfParcel, WorldMap& map, Player* player, GUI& gui) override;
};
// Ghidorah
class GhidorahButton : public AbstractMonsterButton {
public:
	GhidorahButton(sf::RectangleShape& base, const sf::Vector2f buttonPos, const sf::Vector2f buttonSize, const std::string& name, const unsigned& price, const std::string& desc, Textures& textures, const unsigned& gridSize, MonsterStats& stats);
	void clickAtButton(TowerStats& stats, const sf::Vector2<std::size_t>& positionOfParcel, WorldMap& map, Player* player, GUI& gui) override;
};
// Wyvern
class WyvernButton : public AbstractMonsterButton {
public:
	WyvernButton(sf::RectangleShape& base, const sf::Vector2f buttonPos, const sf::Vector2f buttonSize, const std::string& name, const unsigned& price, const std::string& desc, Textures& textures, const unsigned& gridSize, MonsterStats& stats);
	void clickAtButton(TowerStats& stats, const sf::Vector2<std::size_t>& positionOfParcel, WorldMap& map, Player* player, GUI& gui) override;
};
// Dragon
class DragonButton : public AbstractMonsterButton {
public:
	DragonButton(sf::RectangleShape& base, const sf::Vector2f buttonPos, const sf::Vector2f buttonSize, const std::string& name, const unsigned& price, const std::string& desc, Textures& textures, const unsigned& gridSize, MonsterStats& stats);
	void clickAtButton(TowerStats& stats, const sf::Vector2<std::size_t>& positionOfParcel, WorldMap& map, Player* player, GUI& gui) override;
};
/**
	Abstract action Button , behave as action button in game menu , for upgrading and selling towers
*/
class AbstractActionButton : public  AbstractButton {};
/**
	Sell Button , behave as sell button in game menu , for selling tower
*/
class SellButton : public AbstractActionButton {
public:
	SellButton(const sf::Vector2f buttonPos, const sf::Vector2f buttonSize, Textures& textures);
	void cursorAtButton(TowerStats& stats, sf::RectangleShape& base, sf::RenderWindow& window, const sf::Vector2<std::size_t>& positionOfParcel, WorldMap& map) override;
	void clickAtButton(TowerStats& stats, const sf::Vector2<std::size_t>& positionOfParcel, WorldMap& map, Player* player, GUI& gui) override;	
};
/**
	Upgrade Button , behave as upgrading button in game menu , for upgrading tower stats
*/
class UpgradeButton : public AbstractActionButton {
public:
	UpgradeButton(const sf::Vector2f buttonPos, const sf::Vector2f buttonSize, Textures& textures);
	void cursorAtButton(TowerStats& stats, sf::RectangleShape& base, sf::RenderWindow& window, const sf::Vector2<std::size_t>& positionOfParcel, WorldMap& map) override;
	void clickAtButton(TowerStats& stats, const sf::Vector2<std::size_t>& positionOfParcel, WorldMap& map, Player* player, GUI& gui) override;
};
/**
	Abstract Tower Button , behave as tower button in game menu , for creating towers
*/
class AbstractTowerButton : public AbstractButton {
protected:
	unsigned PriceForAction = 0;
	sf::Sprite TowerSprite;
	std::string Description;
	std::string Name;
	TowerStats Stats;
	template <typename T>
	bool Action(TowerStats& stats, const sf::Vector2<std::size_t>& positionOfParcel, WorldMap& map, Player* player) {
		if (player->useGold(PriceForAction))
		{
			map.changeMapObjectAtTower<T>(positionOfParcel, Stats, *player);
			return true;
		}
		return false;
	}
public:
	void initialize(const std::string text, sf::RectangleShape& base, const sf::Vector2f buttonPos, const sf::Vector2f buttonSize, Textures& textures, const unsigned& gridSize);
	std::string generateTowerStatsText();
	void cursorAtButton(TowerStats& stats, sf::RectangleShape& base, sf::RenderWindow& window, const sf::Vector2<std::size_t>& positionOfParcel, WorldMap& map) override;
};
	
//  for buiding tower:

// Archer
class ArcherButton : public AbstractTowerButton {
public:
	ArcherButton(sf::RectangleShape& base, const sf::Vector2f buttonPos, const sf::Vector2f buttonSize, const std::string& name, const unsigned& price, const string& desc, Textures& textures, const unsigned& gridSize, TowerStats& stats);
	void clickAtButton(TowerStats& stats, const sf::Vector2<std::size_t>& positionOfParcel, WorldMap& map, Player* player, GUI& gui) override;
};
// Canon
class CanonButton : public AbstractTowerButton {
public:
	CanonButton(sf::RectangleShape& base, const sf::Vector2f buttonPos, const sf::Vector2f buttonSize, const std::string& name, const unsigned& price, const string& desc, Textures& textures, const unsigned& gridSize, TowerStats& stats);
	void clickAtButton(TowerStats& stats, const sf::Vector2<std::size_t>& positionOfParcel, WorldMap& map, Player* player, GUI& gui) override;
};
// Turret
class TurretButton : public AbstractTowerButton {
public:
	TurretButton(sf::RectangleShape& base, const sf::Vector2f buttonPos, const sf::Vector2f buttonSize, const std::string& name, const unsigned& price, const string& desc, Textures& textures, const unsigned& gridSize, TowerStats& stats);
	void clickAtButton(TowerStats& stats, const sf::Vector2<std::size_t>& positionOfParcel, WorldMap& map, Player* player, GUI& gui) override;
};
// Air (only air)
class AirButton : public AbstractTowerButton {
public:
	AirButton(sf::RectangleShape& base, const sf::Vector2f buttonPos, const sf::Vector2f buttonSize, const std::string& name, const unsigned& price, const string& desc, Textures& textures, const unsigned& gridSize, TowerStats& stats);
	void clickAtButton(TowerStats& stats, const sf::Vector2<std::size_t>& positionOfParcel, WorldMap& map, Player* player, GUI& gui) override;
};
// AirTurret (only air) 
class AirTurretButton : public AbstractTowerButton {
public:
	AirTurretButton(sf::RectangleShape& base, const sf::Vector2f buttonPos, const sf::Vector2f buttonSize, const std::string& name, const unsigned& price, const string& desc, Textures& textures, const unsigned& gridSize, TowerStats& stats);
	void clickAtButton(TowerStats& stats, const sf::Vector2<std::size_t>& positionOfParcel, WorldMap& map, Player* player, GUI& gui) override;
};
// Ice 
class IceButton : public AbstractTowerButton {
public:
	IceButton(sf::RectangleShape& base, const sf::Vector2f buttonPos, const sf::Vector2f buttonSize, const std::string& name, const unsigned& price, const string& desc, Textures& textures, const unsigned& gridSize, TowerStats& stats);
	void clickAtButton(TowerStats& stats, const sf::Vector2<std::size_t>& positionOfParcel, WorldMap& map, Player* player, GUI& gui) override;
};
// Wind (only air) 
class WindButton : public AbstractTowerButton {
public:
	WindButton(sf::RectangleShape& base, const sf::Vector2f buttonPos, const sf::Vector2f buttonSize, const std::string& name, const unsigned& price, const string& desc, Textures& textures, const unsigned& gridSize, TowerStats& stats);
	void clickAtButton(TowerStats& stats, const sf::Vector2<std::size_t>& positionOfParcel, WorldMap& map, Player* player, GUI& gui) override;
};
// Fire 
class FireButton : public AbstractTowerButton {
public:
	FireButton(sf::RectangleShape& base, const sf::Vector2f buttonPos, const sf::Vector2f buttonSize, const std::string& name, const unsigned& price, const string& desc, Textures& textures, const unsigned& gridSize, TowerStats& stats);
	void clickAtButton(TowerStats& stats, const sf::Vector2<std::size_t>& positionOfParcel, WorldMap& map, Player* player, GUI& gui) override;
};
// Poison 
class PoisonButton : public AbstractTowerButton {
public:
	PoisonButton(sf::RectangleShape& base, const sf::Vector2f buttonPos, const sf::Vector2f buttonSize, const std::string& name, const unsigned& price, const string& desc, Textures& textures, const unsigned& gridSize, TowerStats& stats);
	void clickAtButton(TowerStats& stats, const sf::Vector2<std::size_t>& positionOfParcel, WorldMap& map, Player* player, GUI& gui) override;
};
// Storm (only air) 
class StormButton : public AbstractTowerButton {
public:
	StormButton(sf::RectangleShape& base, const sf::Vector2f buttonPos, const sf::Vector2f buttonSize, const std::string& name, const unsigned& price, const string& desc, Textures& textures, const unsigned& gridSize, TowerStats& stats);
	void clickAtButton(TowerStats& stats, const sf::Vector2<std::size_t>& positionOfParcel, WorldMap& map, Player* player, GUI& gui) override;
};
// Explode 
class ExplodeButton : public AbstractTowerButton {
public:
	ExplodeButton(sf::RectangleShape& base, const sf::Vector2f buttonPos, const sf::Vector2f buttonSize, const std::string& name, const unsigned& price, const string& desc, Textures& textures, const unsigned& gridSize, TowerStats& stats);
	void clickAtButton(TowerStats& stats, const sf::Vector2<std::size_t>& positionOfParcel, WorldMap& map, Player* player, GUI& gui) override;
};

