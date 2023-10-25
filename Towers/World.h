///////////////////////////////////////////////////////////
///// Towers! game - Game World
///////////////////////////////////////////////////////////

#pragma once

// headers
#include "Towers.h"
#include "Textures.h"
#include "GameExceptions.h"


// define alias
class ParcelSpace;
using Parcel = shared_ptr<ParcelSpace>;

// class for Game map, its store datas of map and process them
class WorldMap {
public:
	// unsigned Grid size getter
	unsigned getGridSize() { return GridSize; }
	// Float Grid size getter
	float getGridFSize() { return static_cast<float>(GridSize); }
	// Grid size setter
	void setGridSize(unsigned gridSize) { GridSize = gridSize; }
	// method, for load texture
	void setTextures();
	// method, for creating and setting game map as parameter it takes path to file and grid size, which from it will create map
	void createMap(std::string file,const unsigned& gridSize, Player& playerOne, Player& playerTwo);
	// method, which draw all map spaces
	void drawMap(sf::RenderWindow& window);
	ParcelSpace* getParcelAt(sf::Vector2<std::size_t> position);
	sf::Vector2<std::size_t> getMapSize() { return MapSize; }
	std::size_t getMapBound() { return MapBound; }
	// method, after selling some tower , its need to be replace as free space
	void changeMapObjectAtSpace(const sf::Vector2<std::size_t>& position,Player& player) {
		GameMap.at((MapSize.x * position.y) + position.x) = make_shared<SpaceForTower>(sf::Vector2<std::size_t>(position.x, position.y), Textures, GridSize);
		player.getTowerList().Delete((MapSize.x * position.y) + position.x);
	}
	// template method , for building new tower at free space
	template <typename T>
	void changeMapObjectAtTower(const sf::Vector2<std::size_t>& position,TowerStats& stats, Player& player) {
		ListOfTowers pointer = make_shared<T>(sf::Vector2<std::size_t>(position.x, position.y), Textures, GridSize, stats);
		GameMap.at((MapSize.x * position.y) + position.x) = pointer;
		player.getTowerList().Add((MapSize.x * position.y) + position.x, pointer);
	}
	Textures Textures; //data struct for texture
private:
	unsigned GridSize = 0;
	std::size_t MapBound = 0;
	std::vector<Parcel> GameMap; 
	sf::Vector2<std::size_t> MapSize;
	sf::Vector2f getPositionFromFile(const string& text);
};

