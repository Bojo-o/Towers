///////////////////////////////////////////////////////////
///// Towers! game - Direction that represent sequence of direcion(up,down,left,right)
///////////////////////////////////////////////////////////

#pragma once

// headers
#include <SFML/Graphics.hpp>
#include <vector>
#include <string>
#include "GameExceptions.h"

/**
	sequence of direcion (pairs of -1 ,0 and 1 that represent direction)
*/
class Direction {
public:
	// it takes string of WASD* latters and making direction sequence
	void setDirection(const std::string& path);
	// takes index of sequence element and return it as Vector of float 
	sf::Vector2f getDirectionAt(const std::size_t index);
	// return size of Direction sequence
	std::size_t getSize() { return this->Sequence.size(); }
private:
	std::vector<std::pair<short, short>> Sequence;
};