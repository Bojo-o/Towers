///////////////////////////////////////////////////////////
///// Towers! game
///////////////////////////////////////////////////////////

// headers
#include "Towers.h"
#include "UI.h"
#include <cmath>

// namespaces
using namespace sf;

// functions
Vector2f generatePos(const Vector2<std::size_t> position, const unsigned& gridSize) {
	return Vector2f(position.x * static_cast<float>(gridSize), position.y * static_cast<float>(gridSize));
}

// implement Towers_H_

// Spaces
SpaceForTower::SpaceForTower(const Vector2<std::size_t> position,Textures& textures,const unsigned& gridSize) {
	Position = position;
	ShapeCreator::sprite(ParcelImage ,generatePos(position,gridSize),textures.GetTexture("SpaceForTower"), gridSize);
}
void SpaceForTower::click(GUI& menu) {	
	menu.OpenGUI(TowerGUI(Position));
}
SpaceForMonster::SpaceForMonster(const Vector2<std::size_t> position, Textures& textures, const unsigned& gridSize) {
	Position = position;
	ShapeCreator::sprite(ParcelImage , generatePos(position, gridSize), textures.GetTexture("SpaceForMonster"), gridSize);
}
SpaceForBorder::SpaceForBorder(const Vector2<std::size_t> position,Textures& textures, const unsigned& gridSize) {
	Position = position;
	ShapeCreator::sprite(ParcelImage , generatePos(position, gridSize), textures.GetTexture("SpaceForBorder"), gridSize);
}
SpaceForStart::SpaceForStart(const Vector2<std::size_t> position, Textures& textures, const unsigned& gridSize) {
	Position = position;
	ShapeCreator::sprite(ParcelImage, generatePos(position, gridSize), textures.GetTexture("SpaceForStart"), gridSize);
}
void SpaceForStart::click(GUI& menu) {
	menu.OpenGUI(MonsterGUI());
}
SpaceForEnd::SpaceForEnd(const Vector2<std::size_t> position, Textures& textures, const unsigned& gridSize) {
	Position = position;
	ShapeCreator::sprite(ParcelImage , generatePos(position, gridSize), textures.GetTexture("SpaceForEnd"), gridSize);
}
// Towers 
void Tower::click(GUI& menu) {
	menu.OpenGUI(ActionGUI(Position, &Stats));
}
bool Tower::isMonsterInRange(Monsters monster) {
	if (!(monster->isAlive() && monster->isSpawned()))
	{
		return false;
	}
	float x = abs((this->ParcelImage.getPosition().x) - (monster.get()->getPosition().x));
	float y = abs((this->ParcelImage.getPosition().y) - (monster.get()->getPosition().y));
	float distance = sqrt((x * x) + (y * y));
	return distance <= this->Stats.TowerRange;
}
bool Tower::isCooldownZero(Time& currentTime) {
	return currentTime - this->LastAttack > seconds(this->Stats.TowerSpeed);
}
// Archer
ArcherTower::ArcherTower(const Vector2<std::size_t> position, Textures& textures,const unsigned& gridSize,const TowerStats& stats) {
	Stats = stats;
	Position = position;
	initialize(textures, gridSize, "ArcherTower");
}
void ArcherTower::attack(Monsters monster, sf::Time& currentTime,Player& attacker,Player& defender){
	if (monster->Attacked(ArcherAttack(Stats.TowerDamage),attacker,defender))
	{
		LastAttack = currentTime;
	}
}
// Canon
CanonTower::CanonTower(const Vector2<std::size_t> position, Textures& textures, const unsigned& gridSize, const TowerStats& stats) {
	Stats = stats;
	Position = position;
	initialize(textures, gridSize, "CanonTower");
}
void CanonTower::attack(Monsters monster, sf::Time& currentTime, Player& attacker, Player& defender) {
	if (monster->Attacked(CanonAttack(Stats.TowerDamage), attacker, defender))
	{
		LastAttack = currentTime;
	}
}
// Turret
TurretTower::TurretTower(const Vector2<std::size_t> position, Textures& textures, const unsigned& gridSize, const TowerStats& stats) {
	Stats = stats;
	Position = position;
	initialize(textures, gridSize, "TurretTower");
	hasEfect = true;
}
void TurretTower::attack(Monsters monster, sf::Time& currentTime, Player& attacker, Player& defender) {
	if (monster->Attacked(TurretAttack(Stats.TowerDamage), attacker, defender))
	{
		LastAttack = currentTime;
	}
}
// Air
AirTower::AirTower(const Vector2<std::size_t> position, Textures& textures, const unsigned& gridSize, const TowerStats& stats) {
	Stats = stats;
	Position = position;
	initialize(textures, gridSize, "AirTower",Color::Blue);
}
void AirTower::attack(Monsters monster, sf::Time& currentTime, Player& attacker, Player& defender) {
	if (monster->Attacked(AirAttack(Stats.TowerDamage), attacker, defender))
	{
		LastAttack = currentTime;
	}
}
// AirTurret
AirTurretTower::AirTurretTower(const Vector2<std::size_t> position, Textures& textures, const unsigned& gridSize, const TowerStats& stats) {
	Stats = stats;
	Position = position;
	initialize(textures, gridSize, "AirTurretTower", Color::Blue);
	hasEfect = true;
}
void AirTurretTower::attack(Monsters monster, sf::Time& currentTime, Player& attacker, Player& defender) {
	if (monster->Attacked(AirTurretAttack(Stats.TowerDamage), attacker, defender))
	{
		this->LastAttack = currentTime;
	}
}
// Ice
IceTower::IceTower(const Vector2<std::size_t> position, Textures& textures, const unsigned& gridSize, const TowerStats& stats) {
	Stats = stats;
	Position = position;
	initialize(textures, gridSize, "IceTower", Color::White);
	hasEfect = true;
}
void IceTower::attack(Monsters monster, sf::Time& currentTime, Player& attacker, Player& defender) {
	if (monster->Attacked(IceAttack(Percentage(static_cast<unsigned>(Stats.TowerDamage))), attacker, defender))
	{
		LastAttack = currentTime;
	}
}
// Wind
WindTower::WindTower(const Vector2<std::size_t> position, Textures& textures, const unsigned& gridSize, const TowerStats& stats) {
	Stats = stats;
	Position = position;
	initialize(textures, gridSize, "WindTower", Color::Blue);
	hasEfect = true;
}
void WindTower::attack(Monsters monster, sf::Time& currentTime, Player& attacker, Player& defender) {
	if (monster->Attacked(WindAttack(Percentage(static_cast<unsigned>(Stats.TowerDamage))), attacker, defender))
	{
		LastAttack = currentTime;
	}
}
// Fire
FireTower::FireTower(const Vector2<std::size_t> position, Textures& textures, const unsigned& gridSize, const TowerStats& stats) {
	Stats = stats;
	Position = position;
	initialize(textures, gridSize, "FireTower", Color::Red);
	hasEfect = true;
}
void FireTower::attack(Monsters monster, sf::Time& currentTime, Player& attacker, Player& defender) {
	if (monster->Attacked(FireAttack(Stats.TowerDamage), attacker, defender))
	{
		LastAttack = currentTime;
	}
}
// Poison
PoisonTower::PoisonTower(const Vector2<std::size_t> position, Textures& textures, const unsigned& gridSize, const TowerStats& stats) {
	Stats = stats;
	Position = position;
	initialize(textures, gridSize, "PoisonTower", Color::Green);
	hasEfect = true;
}
void PoisonTower::attack(Monsters monster, sf::Time& currentTime, Player& attacker, Player& defender) {
	if (monster->Attacked(PoisonAttack(Stats.TowerDamage), attacker, defender))
	{
		LastAttack = currentTime;
	}
}
// Storm
StormTower::StormTower(const Vector2<std::size_t> position, Textures& textures, const unsigned& gridSize, const TowerStats& stats) {
	Stats = stats;
	Position = position;
	initialize(textures, gridSize, "StormTower", Color::Yellow);
	hasEfect = true;
}
void StormTower::attack(Monsters monster, sf::Time& currentTime, Player& attacker, Player& defender) {
	if (monster->Attacked(StormAttack(Stats.TowerDamage), attacker, defender))
	{
		LastAttack = currentTime;
	}
}
// Explode
ExplodeTower::ExplodeTower(const Vector2<std::size_t> position, Textures& textures, const unsigned& gridSize, const TowerStats& stats) {
	Stats = stats;
	Position = position;
	initialize(textures, gridSize, "ExplodeTower", Color::Magenta);
	hasEfect = true;
}
void ExplodeTower::attack(Monsters monster, sf::Time& currentTime, Player& attacker, Player& defender) {
	if (monster->Attacked(ExplodeAttack(Stats.TowerDamage), attacker, defender))
	{
		LastAttack = currentTime;
	}
}


