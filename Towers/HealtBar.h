///////////////////////////////////////////////////////////
///// Towers! game - Tool for drawing HP Bar 
///////////////////////////////////////////////////////////

#pragma once

// headers
#include <SFML/Graphics.hpp>
#include "SfmlShapes.h"

// object that takes HP info and create HPBar from it and draw it
class HealtBarDrawer {
public:
	// set up monster Max HP
	void setUPMaxHP(const float maxHP) { MaxHP = maxHP; }
	// set up  monsters rest HP
	void setUPHP(const float hp) { HP = hp; }
	// create HP Bar Image and draw it on render window
	void draw(sf::RenderWindow& window,const sf::Vector2f position, const sf::Vector2f size) {
		ShapeCreator::rectangleShape(BaseBar, position, size, false, 2.f,sf::Color::Black,sf::Color::Red);
		window.draw(BaseBar);
		if (HP < 0.f)
		{
			return;
		}
		int hpPercentage = static_cast<int>((HP / MaxHP) * 100);
		ShapeCreator::rectangleShape(HPStatus, position, sf::Vector2f((size.x / 100) * hpPercentage,size.y), false, 0.f, sf::Color::Black, sf::Color::Green);
		window.draw(HPStatus);
	}
private:
	float MaxHP = 0.f;
	float HP = 0.f;
	sf::RectangleShape BaseBar;
	sf::RectangleShape HPStatus;
};