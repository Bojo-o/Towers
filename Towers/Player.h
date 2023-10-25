///////////////////////////////////////////////////////////
///// Towers! game - Player Object
///////////////////////////////////////////////////////////
#pragma once

// headers
#include "Army.h"
#include <string>
#include "Towers.h"
#include "TowersList.h"

// namespaces
using namespace std;


// Player object, which represent players
class Player {
public:
	string Name;
	// Player constructor
	Player() { Gold = 150; HP = 250; Name = "player"; HPBar.setUPMaxHP(250.f); }
	// takes one int argument, process if player has more gold than given value and return bool value
	bool hasPlayerEnoungGold(int value){}
	// takes one unsigned argument, player brought something, return bool if process was sucessful
	bool useGold(unsigned value){
		if (this->Gold >= value)
		{
			this->Gold -= value;
			return true;
		}
		return false;
	}
	// takes unsigned and add gold to player
	void getGold(std::size_t value) { Gold += value; }
	// takes one int argument, player lost HP, return true if player is still alive after damage taken
	void takeDamage(float value){
		if (this->HP - value < 0.f)
		{
			this->HP = 0;
		}
		else
		{
			this->HP -= value;
		}
	}
	// return HP value of player
	float getHpProperty() { return HP; }
	// return Gold value of player
	std::size_t getGoldProperty() { return Gold; }
	// method , for creating stats string
	string getStatsForUI(){ return "Player Name: " + Name + "\n" + "HP: " + to_string(HP) + "\n" + "Gold: " + to_string(Gold) + "\n"; }
	// return reference on Army
	Army& getArmy() { return PlayerArmy; }
	// return reference on Tower list
	TowersList& getTowerList() { return Towers; }
	// draw HPBar
	void drawHP(sf::RenderWindow& window,const sf::Vector2f position, const sf::Vector2f size) {
		HPBar.setUPHP(HP);
		HPBar.draw(window, position, size);
	}
private:
	std::size_t Gold; 
	float HP; 
	Army PlayerArmy;
	TowersList Towers;
	sf::Vector2f StartPosition;
	sf::Vector2f EndPosition;
	HealtBarDrawer HPBar;
};