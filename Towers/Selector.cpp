///////////////////////////////////////////////////////////
///// Towers! game
///////////////////////////////////////////////////////////

// headers
#include "Selector.h"
#include "SfmlShapes.h"

// namespaces
using namespace sf;

// implement Selector_H_
void Selector::SetSelector(Vector2f size, Color outLineColor, float thickness, Vector2f zeroPoint) {
	ShapeCreator::rectangleShape(Selector,Vector2f(0,0), size, false, thickness, outLineColor, Color::Transparent);
	SelectorSize.x = size.x;
	SelectorSize.y = size.y;
	ZeroPoint = zeroPoint;
}
void Selector::UpdateSelectorPosition(Vector2<std::size_t> position) {
	Selector.setPosition(ZeroPoint.x + position.x * SelectorSize.x, ZeroPoint.y + position.y * SelectorSize.y);
}
void Selector::draw(RenderWindow& window) {
	window.draw(Selector);
}
