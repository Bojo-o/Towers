///////////////////////////////////////////////////////////
///// Towers! game
///////////////////////////////////////////////////////////

// headers
#include "Direction.h"

// using namespaces
using namespace sf;
using namespace std;

// implement Direction_H_
void Direction::setDirection(const string& path) {
	for (auto&& x: path)
	{
		switch (x)
		{
		case 'A':
			this->Sequence.push_back(make_pair(-1,0));
			break;
		case 'W':
			this->Sequence.push_back(make_pair(0,-1));
			break;
		case 'S':
			this->Sequence.push_back(make_pair(0,1));
			break;
		case 'D':
			this->Sequence.push_back(make_pair(1,0));
			break;
		default:
			throw FailLoadMap("Path for monsters has wrong format");
			break;
		}
	}
}
Vector2f Direction::getDirectionAt(const size_t index) {
	Vector2f vector;
	if (this->Sequence.size() > index)
	{
		vector.x = this->Sequence.at(index).first;
		vector.y = this->Sequence.at(index).second;
		return vector;
	}
	throw FailLoadMap("Direction index out of range");
}