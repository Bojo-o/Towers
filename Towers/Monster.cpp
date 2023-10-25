///////////////////////////////////////////////////////////
///// Towers! game
///////////////////////////////////////////////////////////

// heaaders
#include "Monster.h"
#include "Player.h"

// namespaces
using namespace sf;

// implement Monster_H_

// functions
float ProcessOffSet(const float& type,const float& position,const float& gridSize) {
	if (type == 1.f)
	{
		return (static_cast<unsigned>(position / gridSize) + 1) * gridSize;
	}
	if (type == -1.f) {
		return static_cast<unsigned>(position / gridSize) * gridSize;
	}	
	return position;
}
// monster
void Monster::checkDeath(Player& attacker, Player& defender) {
	if (isAlive() && Stats.MonsterHP <= 0.f)
	{
		attacker.getArmy().countNewDeadMonster();
		alive = false;
		attacker.getGold(Stats.KilledValue * 2);
		defender.getGold(Stats.KilledValue);
	}
}
void GroundMonster::initialize(const string text,const sf::Vector2f& position, Textures& textures) {
	MonsterSprite.setTexture(textures.GetTexture(text));
	MonsterSprite.setPosition(Vector2f(position.x, position.y));
	MonstersHPBar.setUPMaxHP(Stats.MonsterHP);
}
void AirMonster::initialize(const string text, const sf::Vector2f& position, Textures& textures) {
	MonsterSprite.setTexture(textures.GetTexture(text));
	MonsterSprite.setPosition(Vector2f(position.x, position.y));
	MonsterSprite.setOrigin(Vector2f(0.f,(GridSize / 2.f)));
	MonstersHPBar.setUPMaxHP(Stats.MonsterHP);
}
void GroundMonster::draw(sf::RenderWindow& window) {
	if (spawnStatus && alive)
	{
		window.draw(MonsterSprite);
		MonstersHPBar.setUPHP(Stats.MonsterHP);
		MonstersHPBar.draw(window, Vector2f(MonsterSprite.getPosition().x + 4, MonsterSprite.getPosition().y + 8), Vector2f(56, 12));
	}
};
void AirMonster::draw(sf::RenderWindow& window) {
	if (spawnStatus && alive)
	{
		window.draw(MonsterSprite);
		MonstersHPBar.setUPHP(Stats.MonsterHP);
		MonstersHPBar.draw(window, Vector2f(MonsterSprite.getPosition().x + 4, MonsterSprite.getPosition().y - (GridSize / 2.f) + 8), Vector2f(56, 12));
	}
};
void Monster::move(Direction& direction, Player& attacker, Player& defender) {
	if (spawnStatus && alive)
	{
		if (direction.getSize() == DirectionCount)
		{
			if (alive)
			{
				defender.takeDamage(Stats.MonsterDamage);
				attacker.getArmy().countNewDeadMonster();
				alive = false;
			}
			return;
		}
		Vector2f direct = direction.getDirectionAt(this->DirectionCount);
		if ((MoveCountValue + (Stats.MonsterSpeed * SpeedDeceleration)) >= MoveValue)
		{
			Vector2f newPosition;
			newPosition.x = ProcessOffSet(direct.x, MonsterSprite.getPosition().x, GridSize);
			newPosition.y = ProcessOffSet(direct.y, MonsterSprite.getPosition().y, GridSize);
			MonsterSprite.setPosition(newPosition);
			DirectionCount++;
			MoveCountValue = 0;
		}
		else
		{
			MoveCountValue += Stats.MonsterSpeed * SpeedDeceleration;
			MonsterSprite.move(Vector2f(direct.x * (Stats.MonsterSpeed * SpeedDeceleration), direct.y * (Stats.MonsterSpeed * SpeedDeceleration)));
		}
	}
};

bool GroundMonster::Attacked(ArcherAttack attack, Player& attacker, Player& defender) {
	Stats.MonsterHP -= attack.value;
	checkDeath(attacker, defender);
	return true;
}
bool GroundMonster::Attacked(CanonAttack attack, Player& attacker, Player& defender) {
	Stats.MonsterHP -= attack.value;
	checkDeath(attacker, defender);
	return true;
}
bool GroundMonster::Attacked(TurretAttack attack, Player& attacker, Player& defender) {
	Stats.MonsterHP -= attack.value;
	checkDeath(attacker, defender);
	return true;
}
bool GroundMonster::Attacked(IceAttack attack, Player& attacker, Player& defender) {
	setSpeedDeceleration(attack.value.Value);
	return true;
}
bool GroundMonster::Attacked(FireAttack attack, Player& attacker, Player& defender) {
	Stats.MonsterHP -= attack.value;
	checkDeath(attacker, defender);
	return true;
}
bool GroundMonster::Attacked(PoisonAttack attack, Player& attacker, Player& defender) {
	Stats.MonsterHP -= attack.value;
	checkDeath(attacker, defender);
	return true;
}
bool GroundMonster::Attacked(ExplodeAttack attack, Player& attacker, Player& defender) {
	Stats.MonsterHP = 0;
	checkDeath(attacker, defender);
	return true;
}
bool AirMonster::Attacked(AirAttack attack, Player& attacker, Player& defender) {
	Stats.MonsterHP -= attack.value;
	checkDeath(attacker, defender);
	return true;
}
bool AirMonster::Attacked(AirTurretAttack attack, Player& attacker, Player& defender) {
	Stats.MonsterHP -= attack.value;
	checkDeath(attacker, defender);
	return true;
}
bool AirMonster::Attacked(WindAttack attack, Player& attacker, Player& defender) {
	setSpeedDeceleration(attack.value.Value);
	return true;
}
bool AirMonster::Attacked(StormAttack attack, Player& attacker, Player& defender) {
	Stats.MonsterHP -= attack.value;
	checkDeath(attacker, defender);
	return true;
}
bool AirMonster::Attacked(ExplodeAttack attack, Player& attacker, Player& defender) {
	Stats.MonsterHP = 0;
	checkDeath(attacker, defender);
	return true;
}

Spider::Spider(const sf::Vector2f& position, Textures& textures, const MonsterStats& stats, const float& gridSizeF) {
	Stats = stats;
	GridSize = gridSizeF;
	MoveValue = gridSizeF;
	initialize("Spider", position, textures);
};

IceSpider::IceSpider(const sf::Vector2f& position, Textures& textures, const MonsterStats& stats, const float& gridSizeF)
{
	Stats = stats;
	GridSize = gridSizeF;
	MoveValue = gridSizeF;
	initialize("IceSpider", position, textures);
}

bool IceSpider::Attacked(IceAttack attack, Player& attacker, Player& defender)
{
	setSpeedDeceleration(static_cast<unsigned>(attack.value.Value * 0.5f));
	return true;
}

Ghoul::Ghoul(const sf::Vector2f& position, Textures& textures, const MonsterStats& stats, const float& gridSizeF)
{
	Stats = stats;
	GridSize = gridSizeF;
	MoveValue = gridSizeF;
	initialize("Ghoul", position, textures);
}

bool Ghoul::Attacked(ArcherAttack attack, Player& attacker, Player& defender)
{
	Stats.MonsterHP -= attack.value * 0.3f;
	checkDeath(attacker, defender);
	return true;
}

bool Ghoul::Attacked(CanonAttack attack, Player& attacker, Player& defender)
{
	Stats.MonsterHP -= attack.value * 0.75f;
	checkDeath(attacker, defender);
	return true;
}

bool Ghoul::Attacked(FireAttack attack, Player& attacker, Player& defender)
{
	Stats.MonsterHP -= attack.value * 1.3f;
	checkDeath(attacker, defender);
	return true;
}

Bear::Bear(const sf::Vector2f& position, Textures& textures, const MonsterStats& stats, const float& gridSizeF)
{
	Stats = stats;
	GridSize = gridSizeF;
	MoveValue = gridSizeF;
	initialize("Bear", position, textures);
}

bool Bear::Attacked(CanonAttack attack, Player& attacker, Player& defender)
{
	Stats.MonsterHP -= attack.value * 0.75f;
	checkDeath(attacker, defender);
	return true;
}

IceBear::IceBear(const sf::Vector2f& position, Textures& textures, const MonsterStats& stats, const float& gridSizeF)
{
	Stats = stats;
	GridSize = gridSizeF;
	MoveValue = gridSizeF;
	initialize("IceBear", position, textures);
}

bool IceBear::Attacked(FireAttack attack, Player& attacker, Player& defender)
{
	Stats.MonsterHP -= attack.value * 1.5f;
	checkDeath(attacker, defender);
	return true;
}

Devil::Devil(const sf::Vector2f& position, Textures& textures, const MonsterStats& stats, const float& gridSizeF)
{
	Stats = stats;
	GridSize = gridSizeF;
	MoveValue = gridSizeF;
	initialize("Devil", position, textures);
}

bool Devil::Attacked(ArcherAttack attack, Player& attacker, Player& defender)
{
	Stats.MonsterHP -= attack.value * 0.8f;
	checkDeath(attacker, defender);
	return true;
}

bool Devil::Attacked(CanonAttack attack, Player& attacker, Player& defender)
{
	Stats.MonsterHP -= attack.value * 0.75f;
	checkDeath(attacker, defender);
	return true;
}

Werewolf::Werewolf(const sf::Vector2f& position, Textures& textures, const MonsterStats& stats, const float& gridSizeF)
{
	Stats = stats;
	GridSize = gridSizeF;
	MoveValue = gridSizeF;
	initialize("Werewolf", position, textures);
}

bool Werewolf::Attacked(IceAttack attack, Player& attacker, Player& defender)
{
	setSpeedDeceleration(static_cast<unsigned>(attack.value.Value * 0.3f));
	return true;
}

bool Werewolf::Attacked(ArcherAttack attack, Player& attacker, Player& defender)
{
	Stats.MonsterHP -= attack.value * 0.3f;
	checkDeath(attacker, defender);
	return true;
}

bool Werewolf::Attacked(TurretAttack attack, Player& attacker, Player& defender)
{
	Stats.MonsterHP -= attack.value * 0.3f;
	checkDeath(attacker, defender);
	return true;
}

Golem::Golem(const sf::Vector2f& position, Textures& textures, const MonsterStats& stats, const float& gridSizeF)
{
	Stats = stats;
	GridSize = gridSizeF;
	MoveValue = gridSizeF;
	initialize("Golem", position, textures);
}

bool Golem::Attacked(CanonAttack attack, Player& attacker, Player& defender)
{
	Stats.MonsterHP -= attack.value * 0.75f;
	checkDeath(attacker, defender);
	return true;
}

bool Golem::Attacked(PoisonAttack attack, Player& attacker, Player& defender)
{
	Stats.MonsterHP -= attack.value * 0.75f;
	checkDeath(attacker, defender);
	return true;
}

bool Golem::Attacked(TurretAttack attack, Player& attacker, Player& defender)
{
	Stats.MonsterHP -= attack.value * 0.3f;
	checkDeath(attacker, defender);
	return true;
}

Gargoyle::Gargoyle(const sf::Vector2f& position, Textures& textures, const MonsterStats& stats, const float& gridSizeF)
{
	Stats = stats;
	GridSize = gridSizeF;
	MoveValue = gridSizeF;
	initialize("Gargoyle", position, textures);
}

Pterodactyl::Pterodactyl(const sf::Vector2f& position, Textures& textures, const MonsterStats& stats, const float& gridSizeF)
{
	Stats = stats;
	GridSize = gridSizeF;
	MoveValue = gridSizeF;
	initialize("Pterodactyl", position, textures);
}

bool Pterodactyl::Attacked(WindAttack attack, Player& attacker, Player& defender)
{
	setSpeedDeceleration(static_cast<unsigned>(attack.value.Value * 0.6f));
	return true;
}

bool Pterodactyl::Attacked(AirAttack attack, Player& attacker, Player& defender)
{
	Stats.MonsterHP -= attack.value * 0.75f;
	checkDeath(attacker, defender);
	return true;
}

Ghidorah::Ghidorah(const sf::Vector2f& position, Textures& textures, const MonsterStats& stats, const float& gridSizeF)
{
	Stats = stats;
	GridSize = gridSizeF;
	MoveValue = gridSizeF;
	initialize("Ghidorah", position, textures);
}

bool Ghidorah::Attacked(WindAttack attack, Player& attacker, Player& defender)
{
	setSpeedDeceleration(static_cast<unsigned>(attack.value.Value * 0.8f));
	return true;
}

Wyvern::Wyvern(const sf::Vector2f& position, Textures& textures, const MonsterStats& stats, const float& gridSizeF)
{
	Stats = stats;
	GridSize = gridSizeF;
	MoveValue = gridSizeF;
	initialize("Wyvern", position, textures);
}

bool Wyvern::Attacked(StormAttack attack, Player& attacker, Player& defender)
{
	Stats.MonsterHP -= attack.value * 0.75f;
	checkDeath(attacker, defender);
	return true;
}

bool Wyvern::Attacked(WindAttack attack, Player& attacker, Player& defender)
{
	setSpeedDeceleration(static_cast<unsigned>(attack.value.Value * 0.75f));
	return true;
}

bool Wyvern::Attacked(AirAttack attack, Player& attacker, Player& defender)
{
	Stats.MonsterHP -= attack.value * 0.90f;
	checkDeath(attacker, defender);
	return true;
}

Dragon::Dragon(const sf::Vector2f& position, Textures& textures, const MonsterStats& stats, const float& gridSizeF)
{
	Stats = stats;
	GridSize = gridSizeF;
	MoveValue = gridSizeF;
	initialize("Dragon", position, textures);
}

bool Dragon::Attacked(StormAttack attack, Player& attacker, Player& defender)
{
	Stats.MonsterHP -= attack.value * 0.5f;
	checkDeath(attacker, defender);
	return true;
}

bool Dragon::Attacked(WindAttack attack, Player& attacker, Player& defender)
{
	setSpeedDeceleration(static_cast<unsigned>(attack.value.Value * 0.5f));
	return true;
}

bool Dragon::Attacked(AirTurretAttack attack, Player& attacker, Player& defender)
{
	Stats.MonsterHP -= attack.value * 0.7f;
	checkDeath(attacker, defender);
	return true;
}
