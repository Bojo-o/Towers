///////////////////////////////////////////////////////////
///// Towers! game
///////////////////////////////////////////////////////////

// headers
#include "World.h"
#include <fstream>

// namespaces
using namespace std;
using namespace sf;

// implement WorldMap_H_

void WorldMap::setTextures() {
	// spaces
	Textures.AddNewTexture("SpaceForTower", "textures/ParcelForTower.png");
	Textures.AddNewTexture("SpaceForMonster", "textures/ParcelForMonsters.png");
	Textures.AddNewTexture("SpaceForBorder", "textures/ParcelForBorders.png");
	Textures.AddNewTexture("SpaceForStart", "textures/ParcelForStartPoint.png");
	Textures.AddNewTexture("SpaceForEnd", "textures/ParcelForEndPoint.png");
	// towers
	Textures.AddNewTexture("ArcherTower", "textures/ArcherTower.png");
	Textures.AddNewTexture("ArcherTowerButton", "textures/ArcherTowerButton.png");
	Textures.AddNewTexture("AirTower", "textures/AirTower.png");
	Textures.AddNewTexture("AirTowerButton", "textures/AirTowerButton.png");
	Textures.AddNewTexture("AirTurretTower", "textures/AirTurretTower.png");
	Textures.AddNewTexture("AirTurretTowerButton", "textures/AirTurretTowerButton.png");
	Textures.AddNewTexture("CanonTower", "textures/CanonTower.png");
	Textures.AddNewTexture("CanonTowerButton", "textures/CanonTowerButton.png");
	Textures.AddNewTexture("ExplodeTower", "textures/ExplodeTower.png");
	Textures.AddNewTexture("ExplodeTowerButton", "textures/ExplodeTowerButton.png");
	Textures.AddNewTexture("PoisonTower", "textures/PoisonTower.png");
	Textures.AddNewTexture("PoisonTowerButton", "textures/PoisonTowerButton.png");
	Textures.AddNewTexture("IceTower", "textures/IceTower.png");
	Textures.AddNewTexture("IceTowerButton", "textures/IceTowerButton.png");
	Textures.AddNewTexture("FireTower", "textures/FireTower.png");
	Textures.AddNewTexture("FireTowerButton", "textures/FireTowerButton.png");
	Textures.AddNewTexture("WindTower", "textures/WindTower.png");
	Textures.AddNewTexture("WindTowerButton", "textures/WindTowerButton.png");
	Textures.AddNewTexture("StormTower", "textures/StormTower.png");
	Textures.AddNewTexture("StormTowerButton", "textures/StormTowerButton.png");
	Textures.AddNewTexture("TurretTower", "textures/TurretTower.png");
	Textures.AddNewTexture("TurretTowerButton", "textures/TurretTowerButton.png");
	//actions
	Textures.AddNewTexture("UpgradeButton", "textures/UpgradeButton.png");
	Textures.AddNewTexture("SellButton", "textures/SellButton.png");
	// monsters
	Textures.AddNewTexture("Spider", "textures/Spider.png");
	Textures.AddNewTexture("IceSpider", "textures/IceSpider.png");
	Textures.AddNewTexture("Bear", "textures/Bear.png");
	Textures.AddNewTexture("IceBear", "textures/IceBear.png");
	Textures.AddNewTexture("Devil", "textures/Devil.png");
	Textures.AddNewTexture("Dragon", "textures/Dragon.png");
	Textures.AddNewTexture("Gargoyle", "textures/Gargoyle.png");
	Textures.AddNewTexture("Ghidorah", "textures/Ghidorah.png");
	Textures.AddNewTexture("Ghoul", "textures/Ghoul.png");
	Textures.AddNewTexture("Golem", "textures/Golem.png");
	Textures.AddNewTexture("Pterodactyl", "textures/Pterodactyl.png");
	Textures.AddNewTexture("Werewolf", "textures/Werewolf.png");
	Textures.AddNewTexture("Wyvern", "textures/Wyvern.png");
	
}
// function for parse first line
void GetSplitedParameters(const std::string& text, size_t& xOutPut, size_t& yOutPut) {
	try
	{
		std::string t = "";
		for (auto&& x : text)
		{
			if (x == ' ')
			{
				xOutPut = static_cast<std::size_t>(std::stoull(t));
				t = "";
				continue;
			}
			t += x;
		}
		yOutPut = static_cast<std::size_t>(std::stoull(t));
	}
	catch (const std::exception&)
	{
		throw FailLoadMap(": file has wrong format");
	}
}
Vector2f WorldMap::getPositionFromFile(const string& text) {
	size_t x = 0;
	size_t y = 0;
	GetSplitedParameters(text, x, y);
	return Vector2f(getGridFSize() * (static_cast<float>(x - 1)), getGridFSize() * static_cast<float>(y - 1));
}
void WorldMap::createMap(string file,const unsigned& gridSize,Player& playerOne,Player& playerTwo) {	
	try
	{
		GridSize = gridSize;
		string line;
		ifstream FileReader(file);
		// get first line
		getline(FileReader, line);
		size_t xSize = 0;
		size_t ySize = 0;
		GetSplitedParameters(line, xSize, ySize);
		// set direct
		getline(FileReader, line);
		playerTwo.getArmy().setDirection(line);
		getline(FileReader, line);
		playerOne.getArmy().setDirection(line);
		// position
		getline(FileReader, line);
		playerTwo.getArmy().setStartPosition(getPositionFromFile(line));
		getline(FileReader, line);
		playerOne.getArmy().setStartPosition(getPositionFromFile(line));
		// set map size
		MapSize.x = xSize;
		MapBound = xSize / 2;
		MapSize.y = ySize;
		// counters
		size_t XCounter = 0;
		size_t YCounter = 0;
		// read next lines				
		while (getline(FileReader, line))
		{
		
			if (line == "") { continue; }			
			YCounter += 1;
			XCounter = 0;
			for (auto&& x : line)
			{
				XCounter += 1;
							
				switch (x)
				{
				case 'B':
					GameMap.push_back(make_shared<SpaceForBorder>(Vector2<std::size_t>(XCounter-1,YCounter-1),Textures,gridSize));
					break;
				case 'T':
					GameMap.push_back(make_shared<SpaceForTower>(Vector2<std::size_t>(XCounter - 1, YCounter - 1), Textures, gridSize));
					break;
				case 'M':
					GameMap.push_back(make_shared<SpaceForMonster>(Vector2<std::size_t>(XCounter - 1, YCounter - 1), Textures, gridSize));
					break;
				case 'S':
					GameMap.push_back(make_shared<SpaceForStart>(Vector2<std::size_t>(XCounter - 1, YCounter - 1), Textures, gridSize));
					break;
				case 'E':
					GameMap.push_back(make_shared<SpaceForEnd>(Vector2<std::size_t>(XCounter - 1, YCounter - 1), Textures, gridSize));
					break;
				default:
					throw FailLoadMap(": given datas are invalid");
					break;
				}
				

			}
			if (XCounter != xSize) { throw FailLoadMap(": given datas are invalid, more symbols than expected"); }			
		}	
		if(YCounter != ySize) { throw FailLoadMap(": given datas are invalid, more symbols than expected"); }
		FileReader.close();
	}	
	catch (...)
	{
		throw FailLoadMap("error while loading map data");
	}
}
void WorldMap::drawMap(RenderWindow& window) {
	for (auto&& x :GameMap)
	{
		x.get()->draw(window);
	}
}
ParcelSpace* WorldMap::getParcelAt(Vector2<std::size_t> position) {
	return GameMap.at((MapSize.x * position.y) + position.x).get();
}

