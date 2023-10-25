///////////////////////////////////////////////////////////
///// Towers! game - Static Creator for text
///////////////////////////////////////////////////////////

#pragma once

// headers
#include <SFML/Graphics.hpp>
#include <iostream>

// Static class, that creator text and draw it on render window
class TextCreator {
public:
	// draw text on render window
	static void drawText(sf::RenderWindow& window, const std::string massage, const sf::Vector2f position, const sf::Color color = sf::Color::Black, const unsigned chSize = 16) {
		sf::Font font;
		if (!font.loadFromFile("fonts/arial.ttf"))
		{
			std::cerr << "can not load arial font";
		}
		sf::Text text(massage, font);
		text.setFillColor(color);
		text.setCharacterSize(chSize);
		text.setPosition(position);
		window.draw(text);
	}
};
