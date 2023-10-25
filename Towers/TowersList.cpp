///////////////////////////////////////////////////////////
///// Towers! game
///////////////////////////////////////////////////////////

// headers
#include "TowersList.h"
#include "GameExceptions.h"

// namespaces
using namespace std;
using namespace sf;

// implement TowerList_H_

void TowersList::Add(std::size_t index, ListOfTowers tower) {
	Towers.push_front(tower);
	TowersMap.emplace(pair<std::size_t, list<ListOfTowers>::iterator>(index,Towers.begin()));
}
void TowersList::Delete(std::size_t index) {
	auto it = TowersMap.find(index);
	if (it == TowersMap.end())
	{
		throw FailLoadMap("error");
	}
	Towers.erase(it->second);
	TowersMap.erase(it);
}
