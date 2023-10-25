///////////////////////////////////////////////////////////
///// Towers! game - Static Creator for diffetnt type of Shape
///////////////////////////////////////////////////////////

#pragma once

// headers
#include <SFML/Graphics.hpp>

// static class ,that creating Shapes with set up properties
class ShapeCreator {
public:
	// create circle
	static void circle(sf::CircleShape& circle,const sf::Vector2f position, const float radius, const sf::Color color = sf::Color::Black, const float thickness = 2) {
		circle.setRadius(radius);
		circle.setFillColor(sf::Color::Transparent);
		circle.setOutlineColor(color);
		circle.setOutlineThickness(thickness);
		circle.setPosition(position.x, position.y);
		circle.setOrigin(circle.getRadius(), circle.getRadius());
	}
	// create sprite , size: x and y are same
	static void sprite(sf::Sprite& sprite, const sf::Vector2f position, sf::Texture& texture, const unsigned gridSize) {
		sprite.setTexture(texture);
		sprite.setTextureRect(sf::IntRect(0, 0, static_cast<int>(gridSize), static_cast<int>(gridSize)));
		sprite.setPosition(sf::Vector2f(position.x, position.y));
	}
	// create sprite, size: x and y are not same
	static void sprite(sf::Sprite& sprite, const sf::Vector2f position, sf::Texture& texture, const sf::Vector2f size) {
		sprite.setTexture(texture);
		sprite.setTextureRect(sf::IntRect(0, 0, static_cast<int>(size.x), static_cast<int>(size.y)));
		sprite.setPosition(sf::Vector2f(position.x, position.y));
	}
	// create rectangleShape
	static void rectangleShape(sf::RectangleShape& Shape, const sf::Vector2f positon,const sf::Vector2f size , bool setPositionAsCenter = false,
		const float thickness = 1, const sf::Color outLineColor = sf::Color::Black, const sf::Color fillColor = sf::Color::White) {
		Shape.setFillColor(fillColor);
		Shape.setOutlineColor(outLineColor);
		Shape.setOutlineThickness(thickness);
		Shape.setSize(size);
		Shape.setPosition(positon);
		if (setPositionAsCenter)
		{
			Shape.setOrigin(Shape.getSize().x / 2 , Shape.getSize().y / 2);
		}		
	}
	// create floatRect
	static void floatRect(sf::FloatRect& rect, const sf::Vector2f position, const sf::Vector2f size) {
		rect.left = position.x;
		rect.top = position.y;
		rect.width = size.x;
		rect.height = size.y;
	}
};
