///////////////////////////////////////////////////////////
///// Towers! game - Game Spaces and Towers 
///////////////////////////////////////////////////////////

#pragma once

// Headers
#include <SFML/Graphics.hpp>
#include "Player.h"
#include "Textures.h"
#include "Stats.h"
#include "SfmlShapes.h"

class GUI;

// basic abstract Space for world, parent of all spaces in game
class ParcelSpace {
protected:
	sf::Sprite ParcelImage;
	sf::Vector2<std::size_t> Position;
public:
	// draw parcel space on render window
	void draw(sf::RenderWindow& window) { window.draw(this->ParcelImage); };
	// virtual, after pressing mouse button start click action
	virtual void click(GUI& menu) = 0;
};

// free space for building tower at this space
class SpaceForTower : public ParcelSpace {
public:
	// initialize space propierties as position , texture and size
	SpaceForTower(const sf::Vector2<std::size_t> position, Textures& textures,const unsigned& gridSize);	
	// after pressing mouse button , open GUI for Building towers
	void click(GUI& menu) override;
};
// space where monsters units moves
class SpaceForMonster : public ParcelSpace {
public:
	// initialize space propierties as position , texture and size
	SpaceForMonster(const sf::Vector2<std::size_t> position,Textures& textures,const unsigned& gridSize);	
	// no action for this space
	void click(GUI& menu)override {};
};
// border space
class SpaceForBorder : public ParcelSpace {
public:
	// initialize space propierties as position , texture and size
	SpaceForBorder(const sf::Vector2<std::size_t> position, Textures& textures,const unsigned& gridSize);	
	// no action for this space
	void click(GUI& menu)override {};
};
// space where monsters units spawn
class SpaceForStart : public ParcelSpace {
public:
	// initialize space propierties as position , texture and size
	SpaceForStart(const sf::Vector2<std::size_t> position, Textures& textures,const unsigned& gridSize);
	// after pressing mouse button open GUI for buying monsters units
	void click(GUI& menu)override;
};
// end, goal, space , here try to get units and take damege to player
class SpaceForEnd : public ParcelSpace {
public:
	// initialize space propierties as position , texture and size
	SpaceForEnd(const sf::Vector2<std::size_t> position, Textures& textures,const unsigned& gridSize);	
	// no action
	void click(GUI& menu)override {};
};
// basic abstract tower space , adding more properties for space
class Tower : public ParcelSpace{
protected:
	TowerStats Stats;
	sf::Time LastAttack = sf::seconds(0.f);
	sf::CircleShape RangeCircle;
	bool hasEfect = false;
public:
	// initialize
	void initialize(Textures& textures, const unsigned& gridSize,const std::string textureName, sf::Color color = sf::Color::Black) {
		sf::Vector2f posVector(Position.x * static_cast<float>(gridSize), Position.y * static_cast<float>(gridSize));
		ShapeCreator::sprite(ParcelImage, sf::Vector2f(posVector.x, posVector.y), textures.GetTexture(textureName), gridSize);
		ShapeCreator::circle(RangeCircle, sf::Vector2f(posVector.x + (gridSize / 2.f), posVector.y + (gridSize / 2.f)), Stats.TowerRange, color);
	}
	// takes monster and return true if monster is in tower range
	bool isMonsterInRange(Monsters monster);
	// return true if tower is ready to attack
	bool isCooldownZero(sf::Time& currentTime);
	// reset cooldown
	void resetCooldown(){this->LastAttack = sf::seconds(0.f);}
	// draw range circle around tower
	void drawRangeCircle(sf::RenderWindow& window) { 
		this->RangeCircle.setRadius(this->Stats.TowerRange);
		this->RangeCircle.setOrigin(sf::Vector2f(this->Stats.TowerRange, this->Stats.TowerRange));
		window.draw(this->RangeCircle);
	}
	// after pressing mouse button, open GUI for Action as selling or upgrading
	void click(GUI& menu)override;
	// return true if tower is AOE (do action for all units in range)
	bool hasTowerEfect() { return hasEfect; };
	// virtual, gives attack to monster
	virtual void attack(Monsters monster, sf::Time& currentTime,Player& attacker, Player& defender) = 0;
};
// shoot and takes damage at one ground enemy unit
class ArcherTower : public Tower {
public:
	// initialize tower position, texture, size and stats 
	ArcherTower(const sf::Vector2<std::size_t> position, Textures& textures,const unsigned& gridSize,const TowerStats& stats);	
	// overide attack , gives Archer attack
	void attack(Monsters monster, sf::Time& currentTime,Player& attacker, Player& defender) override;
};
// shoot bigger damage at units, gives more damage to Tank monster
class CanonTower : public Tower {
public:
	// initialize tower position, texture, size and stats 
	CanonTower(const sf::Vector2<std::size_t> position, Textures& textures, const unsigned& gridSize, const TowerStats& stats);
	// overide attack , gives Canon attack
	void attack(Monsters monster, sf::Time& currentTime, Player& attacker, Player& defender) override;
};
// shoot at all ground units at same time
class TurretTower : public Tower {
public:
	// initialize tower position, texture, size and stats 
	TurretTower(const sf::Vector2<std::size_t> position, Textures& textures, const unsigned& gridSize, const TowerStats& stats);
	// overide attack , gives Turret attack
	void attack(Monsters monster, sf::Time& currentTime, Player& attacker, Player& defender) override;
};
// shoot at one air unit
class AirTower : public Tower {
public:
	// initialize tower position, texture, size and stats 
	AirTower(const sf::Vector2<std::size_t> position, Textures& textures, const unsigned& gridSize, const TowerStats& stats);
	// overide attack , gives Air attack
	void attack(Monsters monster, sf::Time& currentTime, Player& attacker, Player& defender) override;
};
// shoot at all air units at same time
class AirTurretTower : public Tower {
public:
	// initialize tower position, texture, size and stats 
	AirTurretTower(const sf::Vector2<std::size_t> position, Textures& textures, const unsigned& gridSize, const TowerStats& stats);
	// overide attack , gives AirTurret attack
	void attack(Monsters monster, sf::Time& currentTime, Player& attacker, Player& defender) override;
};
// slow units 
class IceTower : public Tower {
public:
	// initialize tower position, texture, size and stats 
	IceTower(const sf::Vector2<std::size_t> position, Textures& textures, const unsigned& gridSize, const TowerStats& stats);
	// overide attack , gives Ice attack
	void attack(Monsters monster, sf::Time& currentTime, Player& attacker, Player& defender) override;
};
// slow air units 
class WindTower : public Tower {
public:
	// initialize tower position, texture, size and stats 
	WindTower(const sf::Vector2<std::size_t> position, Textures& textures, const unsigned& gridSize, const TowerStats& stats);
	// overide attack , gives Wind attack
	void attack(Monsters monster, sf::Time& currentTime, Player& attacker, Player& defender) override;
};
// gives fire damage to units
class FireTower : public Tower {
public:
	// initialize tower position, texture, size and stats 
	FireTower(const sf::Vector2<std::size_t> position, Textures& textures, const unsigned& gridSize, const TowerStats& stats);
	// overide attack , gives Fire attack
	void attack(Monsters monster, sf::Time& currentTime, Player& attacker, Player& defender) override;
};
// gives poison to units
class PoisonTower : public Tower {
public:
	// initialize tower position, texture, size and stats 
	PoisonTower(const sf::Vector2<std::size_t> position, Textures& textures, const unsigned& gridSize, const TowerStats& stats);
	// overide attack , gives Poison attack
	void attack(Monsters monster, sf::Time& currentTime, Player& attacker, Player& defender) override;
};
// gives storm damage to all air units in range
class StormTower : public Tower {
public:
	// initialize tower position, texture, size and stats 
	StormTower(const sf::Vector2<std::size_t> position, Textures& textures, const unsigned& gridSize, const TowerStats& stats);
	// overide attack , gives Storm attack
	void attack(Monsters monster, sf::Time& currentTime, Player& attacker, Player& defender) override;
};
// goes big boom , if cooldown reach zero(except units with explode resistant), kill instant units
class ExplodeTower : public Tower {
public:
	// initialize tower position, texture, size and stats 
	ExplodeTower(const sf::Vector2<std::size_t> position, Textures& textures, const unsigned& gridSize, const TowerStats& stats);
	// overide attack , gives Explode attack
	void attack(Monsters monster, sf::Time& currentTime, Player& attacker, Player& defender) override;
};

