///////////////////////////////////////////////////////////
///// Towers! game
///////////////////////////////////////////////////////////

// headers
#include "Buttons.h"
#include <iomanip>
#include <sstream>
#include "SfmlText.h"

// namespaces
using namespace std;
using namespace sf;

// implement Buttons_H_

// genereting details texts
string AbstractTowerButton::generateTowerStatsText() {
	stringstream stream;
	stream << std::fixed << std::setprecision(1) << Name << "\n\nBuild price: " << PriceForAction << "\n\n" <<
		"Description\n" << Description << "\n\nStats\nAttack damage: " << Stats.TowerDamage << "\nAttack speed: " <<
		Stats.TowerSpeed << "\nRange: " << Stats.TowerRange << "\n";
	return stream.str();
}
string AbstractMonsterButton::generateMonsterStatsText() {
	stringstream stream;
	stream << std::fixed << std::setprecision(1) << Name << "\n\nBuy price: " << this->PriceForAction << "\n\n" <<
		"Description\n" << this->Description << "\n\nStats\n Monster Damage: " << this->Stats.MonsterDamage << "\nMonster speed: " <<
		this->Stats.MonsterSpeed << "\nHP: " << this->Stats.MonsterHP << "\n";
	return stream.str();
}
string generateTextForUpgrade(TowerStats& stats) {
	if (stats.Level != 3)
	{
		stringstream stream;
		stream << std::fixed << std::setprecision(1) << "Upgrade this Tower for : \n" << stats.UpgradePrice << " gold\n\nStats\n" <<
			"Attack damage: " << stats.TowerDamage << " -> " << stats.TowerDamage * stats.TowerDamageUpgradeRatio << "\nAttack speed: " <<
			stats.TowerSpeed << " -> " << stats.TowerSpeed * stats.TowerSpeedUpgradeRatio << "\nRange: " << stats.TowerRange <<
			" -> " << stats.TowerRange * stats.TowerRangeUpgradeRatio << "\n";
		return stream.str();
	}
	else
	{
		return "This Tower already has \nmaximum level";
	}
}

// function for generate text position
Vector2f generateTextPos(RectangleShape& base) {
	return Vector2f(base.getPosition().x + 10.f, base.getPosition().y + 10.f);
}

// implemention of Buttons_H_
void AbstractButton::draw(sf::RenderWindow& window) {
	window.draw(ButtonSprite);
}
void AbstractTowerButton::cursorAtButton(TowerStats& stats, sf::RectangleShape& base, sf::RenderWindow& window, const sf::Vector2<std::size_t>& positionOfParcel, WorldMap& map) {
	TextCreator::drawText(window, generateTowerStatsText(), generateTextPos(base));	
	window.draw(TowerSprite);
}
void AbstractMonsterButton::cursorAtButton(TowerStats& stats, sf::RectangleShape& base, sf::RenderWindow& window, const sf::Vector2<std::size_t>& positionOfParcel, WorldMap& map) {
	TextCreator::drawText(window, generateMonsterStatsText(), generateTextPos(base));
	window.draw(MonsterSprite);
}
// towers buttons
void AbstractTowerButton::initialize(const std::string text,sf::RectangleShape& base,const sf::Vector2f buttonPos,const sf::Vector2f buttonSize, Textures& textures, const unsigned& gridSize) {
	Vector2f posVector(base.getPosition().x + base.getSize().x / 4, base.getPosition().y - base.getSize().y / 4);
	ShapeCreator::sprite(TowerSprite, Vector2f(posVector.x, posVector.y), textures.GetTexture(text+"Tower"), gridSize);
	TowerSprite.setOrigin(gridSize / 2.f, gridSize / 2.f);
	ShapeCreator::sprite(ButtonSprite, buttonPos, textures.GetTexture(text+"TowerButton"), buttonSize);
}
// Archer
ArcherButton::ArcherButton(sf::RectangleShape& base, const sf::Vector2f buttonPos, const sf::Vector2f buttonSize, const std::string& name, const unsigned& price, const string& desc, Textures& textures, const unsigned& gridSize, TowerStats& stats) {
	Stats = stats;
	Name = name;
	PriceForAction = price;
	Description = desc;
	initialize("Archer", base, buttonPos, buttonSize, textures, gridSize);
}
void ArcherButton::clickAtButton(TowerStats& stats, const sf::Vector2<std::size_t>& positionOfParcel, WorldMap& map, Player* player, GUI& gui) {
	if (Action<ArcherTower>(stats, positionOfParcel, map, player))
	{
		//gui.
		gui.Close();
	}
}
// Canon
CanonButton::CanonButton(sf::RectangleShape& base, const sf::Vector2f buttonPos, const sf::Vector2f buttonSize, const std::string& name, const unsigned& price, const string& desc, Textures& textures, const unsigned& gridSize, TowerStats& stats) {
	Stats = stats;
	Name = name;
	PriceForAction = price;
	Description = desc;
	initialize("Canon", base, buttonPos, buttonSize, textures, gridSize);
}
void CanonButton::clickAtButton(TowerStats& stats, const sf::Vector2<std::size_t>& positionOfParcel, WorldMap& map, Player* player, GUI& gui) {
	if (Action<CanonTower>(stats, positionOfParcel, map, player))
	{
		gui.Close();
	}
}
// Turret 
TurretButton::TurretButton(sf::RectangleShape& base, const sf::Vector2f buttonPos, const sf::Vector2f buttonSize, const std::string& name, const unsigned& price, const string& desc, Textures& textures, const unsigned& gridSize, TowerStats& stats) {
	Stats = stats;
	Name = name;
	PriceForAction = price;
	Description = desc;
	initialize("Turret", base, buttonPos, buttonSize, textures, gridSize);
}
void TurretButton::clickAtButton(TowerStats& stats, const sf::Vector2<std::size_t>& positionOfParcel, WorldMap& map, Player* player, GUI& gui) {
	if (Action<TurretTower>(stats, positionOfParcel, map, player))
	{
		gui.Close();
	}
}
// Air 
AirButton::AirButton(sf::RectangleShape& base, const sf::Vector2f buttonPos, const sf::Vector2f buttonSize, const std::string& name, const unsigned& price, const string& desc, Textures& textures, const unsigned& gridSize, TowerStats& stats) {
	Stats = stats;
	Name = name;
	PriceForAction = price;
	Description = desc;
	initialize("Air", base, buttonPos, buttonSize, textures, gridSize);
}
void AirButton::clickAtButton(TowerStats& stats, const sf::Vector2<std::size_t>& positionOfParcel, WorldMap& map, Player* player, GUI& gui) {
	if (Action<AirTower>(stats, positionOfParcel, map, player))
	{
		gui.Close();
	}
}
// AirTurret 
AirTurretButton::AirTurretButton(sf::RectangleShape& base, const sf::Vector2f buttonPos, const sf::Vector2f buttonSize, const std::string& name, const unsigned& price, const string& desc, Textures& textures, const unsigned& gridSize, TowerStats& stats) {
	Stats = stats;
	Name = name;
	PriceForAction = price;
	Description = desc;
	initialize("AirTurret", base, buttonPos, buttonSize, textures, gridSize);
}
void AirTurretButton::clickAtButton(TowerStats& stats, const sf::Vector2<std::size_t>& positionOfParcel, WorldMap& map, Player* player, GUI& gui) {
	if (Action<AirTurretTower>(stats, positionOfParcel, map, player))
	{
		gui.Close();
	}
}
// Ice 
IceButton::IceButton(sf::RectangleShape& base, const sf::Vector2f buttonPos, const sf::Vector2f buttonSize, const std::string& name, const unsigned& price, const string& desc, Textures& textures, const unsigned& gridSize, TowerStats& stats) {
	Stats = stats;
	Name = name;
	PriceForAction = price;
	Description = desc;
	initialize("Ice", base, buttonPos, buttonSize, textures, gridSize);
}
void IceButton::clickAtButton(TowerStats& stats, const sf::Vector2<std::size_t>& positionOfParcel, WorldMap& map, Player* player, GUI& gui) {
	if (Action<IceTower>(stats, positionOfParcel, map, player))
	{
		gui.Close();
	}
}
// Wind 
WindButton::WindButton(sf::RectangleShape& base, const sf::Vector2f buttonPos, const sf::Vector2f buttonSize, const std::string& name, const unsigned& price, const string& desc, Textures& textures, const unsigned& gridSize, TowerStats& stats) {
	Stats = stats;
	Name = name;
	PriceForAction = price;
	Description = desc;
	initialize("Wind", base, buttonPos, buttonSize, textures, gridSize);
}
void WindButton::clickAtButton(TowerStats& stats, const sf::Vector2<std::size_t>& positionOfParcel, WorldMap& map, Player* player, GUI& gui) {
	if (Action<WindTower>(stats, positionOfParcel, map, player))
	{
		gui.Close();
	}
}
// Fire 
FireButton::FireButton(sf::RectangleShape& base, const sf::Vector2f buttonPos, const sf::Vector2f buttonSize, const std::string& name, const unsigned& price, const string& desc, Textures& textures, const unsigned& gridSize, TowerStats& stats) {
	Stats = stats;
	Name = name;
	PriceForAction = price;
	Description = desc;
	initialize("Fire", base, buttonPos, buttonSize, textures, gridSize);
}
void FireButton::clickAtButton(TowerStats& stats, const sf::Vector2<std::size_t>& positionOfParcel, WorldMap& map, Player* player, GUI& gui) {
	if (Action<FireTower>(stats, positionOfParcel, map, player))
	{
		gui.Close();
	}
}
// Poison 
PoisonButton::PoisonButton(sf::RectangleShape& base, const sf::Vector2f buttonPos, const sf::Vector2f buttonSize, const std::string& name, const unsigned& price, const string& desc, Textures& textures, const unsigned& gridSize, TowerStats& stats) {
	Stats = stats;
	Name = name;
	PriceForAction = price;
	Description = desc;
	initialize("Poison", base, buttonPos, buttonSize, textures, gridSize);
}
void PoisonButton::clickAtButton(TowerStats& stats, const sf::Vector2<std::size_t>& positionOfParcel, WorldMap& map, Player* player, GUI& gui) {
	if (Action<PoisonTower>(stats, positionOfParcel, map, player))
	{
		gui.Close();
	}
}
// Storm 
StormButton::StormButton(sf::RectangleShape& base, const sf::Vector2f buttonPos, const sf::Vector2f buttonSize, const std::string& name, const unsigned& price, const string& desc, Textures& textures, const unsigned& gridSize, TowerStats& stats) {
	Stats = stats;
	Name = name;
	PriceForAction = price;
	Description = desc;
	initialize("Storm", base, buttonPos, buttonSize, textures, gridSize);
}
void StormButton::clickAtButton(TowerStats& stats, const sf::Vector2<std::size_t>& positionOfParcel, WorldMap& map, Player* player, GUI& gui) {
	if (Action<StormTower>(stats, positionOfParcel, map, player))
	{
		gui.Close();
	}
}
// Explode 
ExplodeButton::ExplodeButton(sf::RectangleShape& base, const sf::Vector2f buttonPos, const sf::Vector2f buttonSize, const std::string& name, const unsigned& price, const string& desc, Textures& textures, const unsigned& gridSize, TowerStats& stats) {
	Stats = stats;
	Name = name;
	PriceForAction = price;
	Description = desc;
	initialize("Explode", base, buttonPos, buttonSize, textures, gridSize);
}
void ExplodeButton::clickAtButton(TowerStats& stats, const sf::Vector2<std::size_t>& positionOfParcel, WorldMap& map, Player* player, GUI& gui) {
	if (Action<ExplodeTower>(stats, positionOfParcel, map, player))
	{
		gui.Close();
	}
}

// action buttons
SellButton::SellButton(const sf::Vector2f buttonPos, const sf::Vector2f buttonSize, Textures& textures) {
	ShapeCreator::sprite(ButtonSprite, buttonPos, textures.GetTexture("SellButton"), buttonSize);
}
void SellButton::clickAtButton(TowerStats& stats, const sf::Vector2<std::size_t>& positionOfParcel, WorldMap& map, Player* player, GUI& gui) {
	player->getGold(stats.SellPrice);
	map.changeMapObjectAtSpace(positionOfParcel,*player);
	gui.Close();
}
void SellButton::cursorAtButton(TowerStats& stats, sf::RectangleShape& base, sf::RenderWindow& window, const sf::Vector2<std::size_t>& positionOfParcel, WorldMap& map) {
	TextCreator::drawText(window, "Sell this Tower for : " + to_string(stats.SellPrice) + " gold", generateTextPos(base));
}
UpgradeButton::UpgradeButton(const sf::Vector2f buttonPos, const sf::Vector2f buttonSize, Textures& textures) {
	ShapeCreator::sprite(ButtonSprite, buttonPos, textures.GetTexture("UpgradeButton"), buttonSize);
}
void UpgradeButton::clickAtButton(TowerStats& stats, const sf::Vector2<std::size_t>& positionOfParcel, WorldMap& map, Player* player, GUI& gui){
	if (stats.Level == 3)
	{
		return;
	}
	if (player->useGold(stats.UpgradePrice))
	{
		stats.Upgrade();
		gui.Close();
	}
}
void UpgradeButton::cursorAtButton(TowerStats& stats, sf::RectangleShape& base, sf::RenderWindow& window, const sf::Vector2<std::size_t>& positionOfParcel, WorldMap& map) {
	TextCreator::drawText(window, generateTextForUpgrade(stats), generateTextPos(base));
}

// monsters buttons
void AbstractMonsterButton::initialize(const std::string text, sf::RectangleShape& base, const sf::Vector2f buttonPos, const sf::Vector2f buttonSize, Textures& textures, const unsigned& gridSize) {
	Vector2f posVector(base.getPosition().x + base.getSize().x / 4, base.getPosition().y - base.getSize().y / 4);
	ShapeCreator::sprite(MonsterSprite, Vector2f(posVector.x, posVector.y), textures.GetTexture(text), gridSize);
	MonsterSprite.setOrigin(gridSize / 2.f, gridSize / 2.f);
	ShapeCreator::sprite(ButtonSprite, buttonPos, textures.GetTexture(text), buttonSize); // pridat este "Button"
}
SpiderButton::SpiderButton(sf::RectangleShape& base, const sf::Vector2f buttonPos, const sf::Vector2f buttonSize,const std::string& name,const unsigned& price,const std::string& desc, Textures& textures,const unsigned& gridSize, MonsterStats& stats) {
	Stats = stats;
	Name = name;
	PriceForAction = price;
	Description = desc;
	initialize("Spider", base, buttonPos, buttonSize, textures, gridSize);
}

void SpiderButton::clickAtButton(TowerStats& stats, const sf::Vector2<std::size_t>& positionOfParcel, WorldMap& map, Player* player, GUI& gui) {
	if (player->useGold(PriceForAction))
	{
		gui.increaseNumberAtButton();
		player->getArmy().addMonsterToArmy<Spider>(map.Textures, Stats, map.getGridFSize());		
	}
}

IceSpiderButton::IceSpiderButton(sf::RectangleShape& base, const sf::Vector2f buttonPos, const sf::Vector2f buttonSize, const std::string& name, const unsigned& price, const std::string& desc, Textures& textures, const unsigned& gridSize, MonsterStats& stats)
{
	Stats = stats;
	Name = name;
	PriceForAction = price;
	Description = desc;
	initialize("IceSpider", base, buttonPos, buttonSize, textures, gridSize);
}

void IceSpiderButton::clickAtButton(TowerStats& stats, const sf::Vector2<std::size_t>& positionOfParcel, WorldMap& map, Player* player, GUI& gui)
{
	if (player->useGold(PriceForAction))
	{
		gui.increaseNumberAtButton();
		player->getArmy().addMonsterToArmy<IceSpider>(map.Textures, Stats, map.getGridFSize());
	}
}

GhoulButton::GhoulButton(sf::RectangleShape& base, const sf::Vector2f buttonPos, const sf::Vector2f buttonSize, const std::string& name, const unsigned& price, const std::string& desc, Textures& textures, const unsigned& gridSize, MonsterStats& stats)
{
	Stats = stats;
	Name = name;
	PriceForAction = price;
	Description = desc;
	initialize("Ghoul", base, buttonPos, buttonSize, textures, gridSize);
}

void GhoulButton::clickAtButton(TowerStats& stats, const sf::Vector2<std::size_t>& positionOfParcel, WorldMap& map, Player* player, GUI& gui)
{
	if (player->useGold(PriceForAction))
	{
		gui.increaseNumberAtButton();
		player->getArmy().addMonsterToArmy<Ghoul>(map.Textures, Stats, map.getGridFSize());
	}
}

BearButton::BearButton(sf::RectangleShape& base, const sf::Vector2f buttonPos, const sf::Vector2f buttonSize, const std::string& name, const unsigned& price, const std::string& desc, Textures& textures, const unsigned& gridSize, MonsterStats& stats)
{
	Stats = stats;
	Name = name;
	PriceForAction = price;
	Description = desc;
	initialize("Bear", base, buttonPos, buttonSize, textures, gridSize);
}

void BearButton::clickAtButton(TowerStats& stats, const sf::Vector2<std::size_t>& positionOfParcel, WorldMap& map, Player* player, GUI& gui)
{
	if (player->useGold(PriceForAction))
	{
		gui.increaseNumberAtButton();
		player->getArmy().addMonsterToArmy<Bear>(map.Textures, Stats, map.getGridFSize());
	}
}

IceBearButton::IceBearButton(sf::RectangleShape& base, const sf::Vector2f buttonPos, const sf::Vector2f buttonSize, const std::string& name, const unsigned& price, const std::string& desc, Textures& textures, const unsigned& gridSize, MonsterStats& stats)
{
	Stats = stats;
	Name = name;
	PriceForAction = price;
	Description = desc;
	initialize("IceBear", base, buttonPos, buttonSize, textures, gridSize);
}

void IceBearButton::clickAtButton(TowerStats& stats, const sf::Vector2<std::size_t>& positionOfParcel, WorldMap& map, Player* player, GUI& gui)
{
	if (player->useGold(PriceForAction))
	{
		gui.increaseNumberAtButton();
		player->getArmy().addMonsterToArmy<IceBear>(map.Textures, Stats, map.getGridFSize());
	}
}

DevilButton::DevilButton(sf::RectangleShape& base, const sf::Vector2f buttonPos, const sf::Vector2f buttonSize, const std::string& name, const unsigned& price, const std::string& desc, Textures& textures, const unsigned& gridSize, MonsterStats& stats)
{
	Stats = stats;
	Name = name;
	PriceForAction = price;
	Description = desc;
	initialize("Devil", base, buttonPos, buttonSize, textures, gridSize);
}

void DevilButton::clickAtButton(TowerStats& stats, const sf::Vector2<std::size_t>& positionOfParcel, WorldMap& map, Player* player, GUI& gui)
{
	if (player->useGold(PriceForAction))
	{
		gui.increaseNumberAtButton();
		player->getArmy().addMonsterToArmy<Devil>(map.Textures, Stats, map.getGridFSize());
	}
}

WerewolfButton::WerewolfButton(sf::RectangleShape& base, const sf::Vector2f buttonPos, const sf::Vector2f buttonSize, const std::string& name, const unsigned& price, const std::string& desc, Textures& textures, const unsigned& gridSize, MonsterStats& stats)
{
	Stats = stats;
	Name = name;
	PriceForAction = price;
	Description = desc;
	initialize("Werewolf", base, buttonPos, buttonSize, textures, gridSize);
}

void WerewolfButton::clickAtButton(TowerStats& stats, const sf::Vector2<std::size_t>& positionOfParcel, WorldMap& map, Player* player, GUI& gui)
{
	if (player->useGold(PriceForAction))
	{
		gui.increaseNumberAtButton();
		player->getArmy().addMonsterToArmy<Werewolf>(map.Textures, Stats, map.getGridFSize());
	}
}

GolemButton::GolemButton(sf::RectangleShape& base, const sf::Vector2f buttonPos, const sf::Vector2f buttonSize, const std::string& name, const unsigned& price, const std::string& desc, Textures& textures, const unsigned& gridSize, MonsterStats& stats)
{
	Stats = stats;
	Name = name;
	PriceForAction = price;
	Description = desc;
	initialize("Golem", base, buttonPos, buttonSize, textures, gridSize);
}

void GolemButton::clickAtButton(TowerStats& stats, const sf::Vector2<std::size_t>& positionOfParcel, WorldMap& map, Player* player, GUI& gui)
{
	if (player->useGold(PriceForAction))
	{
		gui.increaseNumberAtButton();
		player->getArmy().addMonsterToArmy<Golem>(map.Textures, Stats, map.getGridFSize());
	}
}

GargoyleButton::GargoyleButton(sf::RectangleShape& base, const sf::Vector2f buttonPos, const sf::Vector2f buttonSize, const std::string& name, const unsigned& price, const std::string& desc, Textures& textures, const unsigned& gridSize, MonsterStats& stats)
{
	Stats = stats;
	Name = name;
	PriceForAction = price;
	Description = desc;
	initialize("Gargoyle", base, buttonPos, buttonSize, textures, gridSize);
}

void GargoyleButton::clickAtButton(TowerStats& stats, const sf::Vector2<std::size_t>& positionOfParcel, WorldMap& map, Player* player, GUI& gui)
{
	if (player->useGold(PriceForAction))
	{
		gui.increaseNumberAtButton();
		player->getArmy().addMonsterToArmy<Gargoyle>(map.Textures, Stats, map.getGridFSize());
	}
}

PterodactylButton::PterodactylButton(sf::RectangleShape& base, const sf::Vector2f buttonPos, const sf::Vector2f buttonSize, const std::string& name, const unsigned& price, const std::string& desc, Textures& textures, const unsigned& gridSize, MonsterStats& stats)
{
	Stats = stats;
	Name = name;
	PriceForAction = price;
	Description = desc;
	initialize("Pterodactyl", base, buttonPos, buttonSize, textures, gridSize);
}

void PterodactylButton::clickAtButton(TowerStats& stats, const sf::Vector2<std::size_t>& positionOfParcel, WorldMap& map, Player* player, GUI& gui)
{
	if (player->useGold(PriceForAction))
	{
		gui.increaseNumberAtButton();
		player->getArmy().addMonsterToArmy<Pterodactyl>(map.Textures, Stats, map.getGridFSize());
	}
}

GhidorahButton::GhidorahButton(sf::RectangleShape& base, const sf::Vector2f buttonPos, const sf::Vector2f buttonSize, const std::string& name, const unsigned& price, const std::string& desc, Textures& textures, const unsigned& gridSize, MonsterStats& stats)
{
	Stats = stats;
	Name = name;
	PriceForAction = price;
	Description = desc;
	initialize("Ghidorah", base, buttonPos, buttonSize, textures, gridSize);
}

void GhidorahButton::clickAtButton(TowerStats& stats, const sf::Vector2<std::size_t>& positionOfParcel, WorldMap& map, Player* player, GUI& gui)
{
	if (player->useGold(PriceForAction))
	{
		gui.increaseNumberAtButton();
		player->getArmy().addMonsterToArmy<Ghidorah>(map.Textures, Stats, map.getGridFSize());
	}
}

WyvernButton::WyvernButton(sf::RectangleShape& base, const sf::Vector2f buttonPos, const sf::Vector2f buttonSize, const std::string& name, const unsigned& price, const std::string& desc, Textures& textures, const unsigned& gridSize, MonsterStats& stats)
{
	Stats = stats;
	Name = name;
	PriceForAction = price;
	Description = desc;
	initialize("Wyvern", base, buttonPos, buttonSize, textures, gridSize);
}

void WyvernButton::clickAtButton(TowerStats& stats, const sf::Vector2<std::size_t>& positionOfParcel, WorldMap& map, Player* player, GUI& gui)
{
	if (player->useGold(PriceForAction))
	{
		gui.increaseNumberAtButton();
		player->getArmy().addMonsterToArmy<Wyvern>(map.Textures, Stats, map.getGridFSize());
	}
}

DragonButton::DragonButton(sf::RectangleShape& base, const sf::Vector2f buttonPos, const sf::Vector2f buttonSize, const std::string& name, const unsigned& price, const std::string& desc, Textures& textures, const unsigned& gridSize, MonsterStats& stats)
{
	Stats = stats;
	Name = name;
	PriceForAction = price;
	Description = desc;
	initialize("Dragon", base, buttonPos, buttonSize, textures, gridSize);
}

void DragonButton::clickAtButton(TowerStats& stats, const sf::Vector2<std::size_t>& positionOfParcel, WorldMap& map, Player* player, GUI& gui)
{
	if (player->useGold(PriceForAction))
	{
		gui.increaseNumberAtButton();
		player->getArmy().addMonsterToArmy<Dragon>(map.Textures, Stats, map.getGridFSize());
	}
}
