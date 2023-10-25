///////////////////////////////////////////////////////////
///// Towers! game - Game monster units
///////////////////////////////////////////////////////////

#pragma once

// headers
#include <SFML/Graphics.hpp>
#include "Textures.h"
#include "Direction.h"
#include "Stats.h"
#include "Attack.h"
#include "HealtBar.h"

class Player;

//  basic abstract monster , parent of all monsters in game
class Monster {
protected:
	sf::Sprite MonsterSprite;
	MonsterStats Stats;
	float SpeedDeceleration = 1;
	float MoveCountValue = 0.f;
	float MoveValue = 0.f;
	float GridSize= 0.f;
	unsigned DirectionCount = 0;
	bool spawnStatus = false;
	bool alive = true;
	HealtBarDrawer MonstersHPBar;
public:
	// chceck if monster after attack is still alive
	void checkDeath(Player& attacker, Player& defender);
	// set up Speed slowness , it takes percentage value
	void setSpeedDeceleration(const unsigned value) { SpeedDeceleration = 1 - (value / 100.f); }
	// return vector2f of monster position
	sf::Vector2f getPosition() { return MonsterSprite.getPosition(); }
	bool isAlive() { if (alive) { return true; }return false; }
	bool isSpawned() { if (spawnStatus) { return true; }return false; }
	// virtual draw Monster on position on render window
	virtual void draw(sf::RenderWindow& window) = 0;
	// spawn monster , if monster has been spawned it can start move
	void spawn() { spawnStatus = true; };
	// move Monster 
	void move(Direction& direction, Player& attacker, Player& defender);
	// virtual all attacks types from tower
	virtual bool Attacked(ArcherAttack attack, Player& attacker, Player& defender) = 0;
	virtual bool Attacked(CanonAttack attack, Player& attacker, Player& defender) = 0;
	virtual bool Attacked(TurretAttack attack, Player& attacker, Player& defender) = 0;
	virtual bool Attacked(AirAttack attack, Player& attacker, Player& defender) = 0;
	virtual bool Attacked(AirTurretAttack attack, Player& attacker, Player& defender) = 0;
	virtual bool Attacked(IceAttack attack, Player& attacker, Player& defender) = 0;
	virtual bool Attacked(WindAttack attack, Player& attacker, Player& defender) = 0;
	virtual bool Attacked(FireAttack attack, Player& attacker, Player& defender) = 0;
	virtual bool Attacked(PoisonAttack attack, Player& attacker, Player& defender) = 0;
	virtual bool Attacked(StormAttack attack, Player& attacker, Player& defender) = 0;
	virtual bool Attacked(ExplodeAttack attack, Player& attacker, Player& defender) = 0;
};
// Ground Monsters
class GroundMonster : public Monster {
public:
	void initialize(const std::string text, const sf::Vector2f& position, Textures& textures);
	void draw(sf::RenderWindow& window) override;
	bool Attacked(ArcherAttack attack, Player& attacker, Player& defender)override;
	bool Attacked(CanonAttack attack, Player& attacker, Player& defender) override;
	bool Attacked(TurretAttack attack, Player& attacker, Player& defender) override;
	bool Attacked(AirAttack attack, Player& attacker, Player& defender) override { return false; }
	bool Attacked(AirTurretAttack attack, Player& attacker, Player& defender) override { return false; }
	bool Attacked(IceAttack attack, Player& attacker, Player& defender) override;
	bool Attacked(WindAttack attack, Player& attacker, Player& defender) override { return false; }
	bool Attacked(FireAttack attack, Player& attacker, Player& defender) override;
	bool Attacked(PoisonAttack attack, Player& attacker, Player& defender) override;
	bool Attacked(StormAttack attack, Player& attacker, Player& defender) override { return false; }
	bool Attacked(ExplodeAttack attack, Player& attacker, Player& defender) override;
};
// Air Monsters
class AirMonster : public Monster {
public:
	void initialize(const std::string text, const sf::Vector2f& position, Textures& textures);
	void draw(sf::RenderWindow& window) override;
	bool Attacked(ArcherAttack attack, Player& attacker, Player& defender)override { return false; }
	bool Attacked(CanonAttack attack, Player& attacker, Player& defender) override { return false; }
	bool Attacked(TurretAttack attack, Player& attacker, Player& defender) override { return false; }
	bool Attacked(AirAttack attack, Player& attacker, Player& defender) override;
	bool Attacked(AirTurretAttack attack, Player& attacker, Player& defender) override;
	bool Attacked(IceAttack attack, Player& attacker, Player& defender) override { return false; }
	bool Attacked(WindAttack attack, Player& attacker, Player& defender) override;
	bool Attacked(FireAttack attack, Player& attacker, Player& defender) override { return false; }
	bool Attacked(PoisonAttack attack, Player& attacker, Player& defender) override { return false; }
	bool Attacked(StormAttack attack, Player& attacker, Player& defender) override;
	bool Attacked(ExplodeAttack attack, Player& attacker, Player& defender) override;
};

// Ground 

//Spider
class Spider : public GroundMonster {
public:
	Spider() {};
	Spider(const sf::Vector2f& position, Textures& textures, const MonsterStats& stats, const float& gridSizeF);	
};
//Ice spider, Ice attack resistance 50%
class IceSpider : public Spider {
public:
	IceSpider(const sf::Vector2f& position, Textures& textures, const MonsterStats& stats, const float& gridSizeF);
	bool Attacked(IceAttack attack, Player& attacker, Player& defender) override;
};
//Ghoul, Archer attack resistance 70% , Canon attack resistance 25% , Poison attack ignore , Fire attack deals 30% more damage
class Ghoul : public GroundMonster {
public:
	Ghoul(const sf::Vector2f& position, Textures& textures, const MonsterStats& stats, const float& gridSizeF);
	bool Attacked(ArcherAttack attack, Player& attacker, Player& defender) override;
	bool Attacked(CanonAttack attack, Player& attacker, Player& defender) override;
	bool Attacked(PoisonAttack attack, Player& attacker, Player& defender) override { return false; };
	bool Attacked(FireAttack attack, Player& attacker, Player& defender) override;
};
//Bear, Archer attack ignore , Canon attack resistance 25%
class Bear : public GroundMonster {
public:
	Bear() {};
	Bear(const sf::Vector2f& position, Textures& textures, const MonsterStats& stats, const float& gridSizeF);
	bool Attacked(ArcherAttack attack, Player& attacker, Player& defender) override { return false; };
	bool Attacked(CanonAttack attack, Player& attacker, Player& defender) override;
};
//Ice Bear,  Archer attack ignore , Canon attack resistance 25% , Ice attack ignore , Fire attack deals 50% more damage
class IceBear : public Bear {
public:
	IceBear(const sf::Vector2f& position, Textures& textures, const MonsterStats& stats, const float& gridSizeF);
	bool Attacked(IceAttack attack, Player& attacker, Player& defender) override { return false; };
	bool Attacked(FireAttack attack, Player& attacker, Player& defender) override;
};
//Devil, Archer attack resistance 20% , Canon attack resistance 25% , Fire attack ignore
class Devil : public GroundMonster {
public:
	Devil(const sf::Vector2f& position, Textures& textures, const MonsterStats& stats, const float& gridSizeF);
	bool Attacked(FireAttack attack, Player& attacker, Player& defender) override { return false; };
	bool Attacked(ArcherAttack attack, Player& attacker, Player& defender) override;
	bool Attacked(CanonAttack attack, Player& attacker, Player& defender) override;
};
//Werewolf, Ice attack resistance 70% , Archer attack resistance 30% , Turret attack resistance 30%
class Werewolf : public GroundMonster {
public:
	Werewolf(const sf::Vector2f& position, Textures& textures, const MonsterStats& stats, const float& gridSizeF);
	bool Attacked(IceAttack attack, Player& attacker, Player& defender) override;
	bool Attacked(ArcherAttack attack, Player& attacker, Player& defender) override;
	bool Attacked(TurretAttack attack, Player& attacker, Player& defender) override;
};
//Golem, Archer attack ignore , Canon attack resistance 25% , Fire attack ignore , Poison attack resistance 25% , Turret attack resistance 70%
class Golem : public GroundMonster {
public:
	Golem(const sf::Vector2f& position, Textures& textures, const MonsterStats& stats, const float& gridSizeF);
	bool Attacked(ArcherAttack attack, Player& attacker, Player& defender) override { return false; };
	bool Attacked(CanonAttack attack, Player& attacker, Player& defender) override;
	bool Attacked(FireAttack attack, Player& attacker, Player& defender) override { return false; };
	bool Attacked(PoisonAttack attack, Player& attacker, Player& defender) override;
	bool Attacked(TurretAttack attack, Player& attacker, Player& defender) override;
};

// Air

//Gargoyle
class Gargoyle : public AirMonster {
public:
	Gargoyle(const sf::Vector2f& position, Textures& textures, const MonsterStats& stats, const float& gridSizeF);
};
//Pterodactyl , Wind attack resistance 40% , Air attack resistance 25%
class Pterodactyl : public AirMonster {
public:
	Pterodactyl(const sf::Vector2f& position, Textures& textures, const MonsterStats& stats, const float& gridSizeF);
	bool Attacked(WindAttack attack, Player& attacker, Player& defender) override;
	bool Attacked(AirAttack attack, Player& attacker, Player& defender) override;
};
//Ghidorah , Wind attack resistance 20% , Storm attack ignore
class Ghidorah : public AirMonster {
public:
	Ghidorah(const sf::Vector2f& position, Textures& textures, const MonsterStats& stats, const float& gridSizeF);
	bool Attacked(StormAttack attack, Player& attacker, Player& defender) override { return false; };
	bool Attacked(WindAttack attack, Player& attacker, Player& defender) override;
};
//Wyvern , Wind attack resistance 25% , Storm attack resistance 25% , Air attack resistance 10%
class Wyvern : public AirMonster {
public:
	Wyvern(const sf::Vector2f& position, Textures& textures, const MonsterStats& stats, const float& gridSizeF);
	bool Attacked(StormAttack attack, Player& attacker, Player& defender) override;
	bool Attacked(WindAttack attack, Player& attacker, Player& defender) override;
	bool Attacked(AirAttack attack, Player& attacker, Player& defender) override;
};
//Dragon , Wind attack resistance 50% , Storm attack resistance 50% , AirTurret attack resistance 30%
class Dragon : public AirMonster {
public:
	Dragon(const sf::Vector2f& position, Textures& textures, const MonsterStats& stats, const float& gridSizeF);
	bool Attacked(StormAttack attack, Player& attacker, Player& defender) override;
	bool Attacked(WindAttack attack, Player& attacker, Player& defender) override;
	bool Attacked(AirTurretAttack attack, Player& attacker, Player& defender) override;
};