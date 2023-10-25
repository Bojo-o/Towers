/////
// Define Army that simply represent all player units of monsters
/////
#pragma once

// headers
#include "Monster.h"
#include <vector>

// declare 
class Monster;
using Monsters = std::shared_ptr<Monster>;
/**
	Object Army that represent behavior of Army, Army contains objects monsters
*/
class Army {
public:
	// Army has member m_armyMoveLineDirection, calling this with string represent path(WASD* letters) it will set up this member
	void setDirection(const std::string& path) {ArmyMoveLineDirection.setDirection(path);}
	// initialize starting point of army, where army will spawns monsters
	void setStartPosition(const sf::Vector2f startPosition) {PositionOfSpawningSpace = startPosition;}
	// template, as typename T it takes Monsters types, it add new monster to army
	template <typename T>
	void addMonsterToArmy(Textures& textures,const MonsterStats& stats,const float gridSizeF) {
		Army.push_back(std::make_shared<T>(this->PositionOfSpawningSpace,textures,stats,gridSizeF));
	}
	// as argument it takes two players and do move(acording to direction line of amry) with all monsters register in this army
	void moveArmy(Player& attacker, Player& defender) {
		for (auto&& x : Army){x.get()->move(ArmyMoveLineDirection,attacker,defender);}
	}
	// draw all units of army at window
	void drawArmy(sf::RenderWindow& window) {
		for (auto&& x : Army){x.get()->draw(window);}
	}
	// spawn one unit monster, in case that already all units has been spawned , it will do nothing
	void spawnMonster() {
		if (Army.size() > IndexOfFirstNotSpawnedMonster)
		{
			Army.at(IndexOfFirstNotSpawnedMonster)->spawn();
			IndexOfFirstNotSpawnedMonster++;
		}
	}
	// calling this, it remove/clear all units from army and initialize members
	void clearArmy() {
		Army.clear();
		DeadMonstersCounter = 0;
		IndexOfFirstNotSpawnedMonster = 0;
	}
	// return true if all units of army are dead
	bool isArmyDead() { return Army.size() == DeadMonstersCounter; }
	// counting dead monsters, calling this it increase counter
	void countNewDeadMonster() {DeadMonstersCounter += 1;}
	// return army size
	//unsigned getArmySize() { return Army.size(); }
	// army iterator that iterate army and return iterator at monster
	class iterator {
	public:
		iterator(std::vector<Monsters>& army) { it = army.begin(); }
		iterator(std::vector<Monsters>& army, bool) { it = army.end(); }
		iterator& operator++() { it++; return *this; }
		Monsters operator*() { return *it; }
		bool operator!=(iterator& second) {
			return it != second.it;
		}
		std::vector<Monsters>::iterator it;
	};
	iterator begin() { return iterator(Army); }
	iterator end() { return iterator(Army, true); }
private:
	std::vector<Monsters> Army;
	unsigned DeadMonstersCounter = 0;
	Direction ArmyMoveLineDirection;
	sf::Vector2f PositionOfSpawningSpace;
	unsigned IndexOfFirstNotSpawnedMonster = 0;
};