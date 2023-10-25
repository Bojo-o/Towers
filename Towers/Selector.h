///////////////////////////////////////////////////////////
///// Towers! game - Selector , object for draw grid where mouse postion is
///////////////////////////////////////////////////////////

#pragma once

// headers
#include <SFML/Graphics.hpp>

// object Selector, its for helping to see where is mouse on game map
class Selector {
public:
	// set up Selector, takes one mandatory argument unsigned size and two no mandatory argument, represent color(default Blue) and thickness(default 1.f)
	void SetSelector(sf::Vector2f size, sf::Color outLineColor, float thickness, sf::Vector2f zeroPoint);
	// takes Vector2<std::size_t> position and update Selector positon
	void UpdateSelectorPosition(sf::Vector2<std::size_t> position);
	// takes RenderWindow and on it draw Selector
	void draw(sf::RenderWindow& window);
	// return size of Selector
	sf::Vector2f& GetSize() { return SelectorSize; }
private:
	sf::Vector2f ZeroPoint;
	sf::Vector2f SelectorSize;
	sf::RectangleShape Selector;
};