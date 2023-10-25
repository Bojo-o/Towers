///////////////////////////////////////////////////////////
///// Towers! game - Tower List for knowledge , where are Towers
///////////////////////////////////////////////////////////

#pragma once

// headers
#include <map>
#include <list>
#include <SFML/Graphics.hpp>

class Tower;
using ListOfTowers = std::shared_ptr<Tower>; // define alias

// Tower List , serve for storing pointers pointing at towers on game world
class TowersList {
public:
	void Add(std::size_t index, ListOfTowers tower);
	void Delete(std::size_t index);
	std::size_t getSize() { return Towers.size(); }
	class iterator {
	public:
		iterator(std::list<ListOfTowers>& towers) { it = towers.begin(); }
		iterator(std::list<ListOfTowers>& towers, bool) { it = towers.end(); }
		iterator& operator++() { it++; return *this; }
		ListOfTowers operator*() { return *it; }
		bool operator!=(iterator& second) {
			return it != second.it;
		}
		std::list<ListOfTowers>::iterator it;
	};
	iterator begin() { return iterator(Towers); }
	iterator end() { return iterator(Towers,true); }
private:
	std::map<std::size_t, std::list<ListOfTowers>::iterator> TowersMap;
	std::list<ListOfTowers> Towers;
};