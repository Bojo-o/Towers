///////////////////////////////////////////////////////////
///// Towers! game
///////////////////////////////////////////////////////////

// headers
#include "Textures.h"
#include "GameExceptions.h"

// namespaces
using namespace sf;
using namespace std;

// implement Texture_H_

void Textures::AddNewTexture(string NameOftexture, string PathToTextureData) {
	sf::Texture texture;
	if (!texture.loadFromFile(PathToTextureData))
	{
		throw FailLoadMap("can not load texture: " + PathToTextureData);
	}
	GameTextures.insert(pair<string, Texture>(NameOftexture, texture)); 
}
Texture& Textures::GetTexture(std::string NameOftexture) {
	GameTexturesIterator = GameTextures.find(NameOftexture);
	if (GameTexturesIterator == GameTextures.end())
	{
		throw FailLoadMap(NameOftexture + " texture do not exist");
	}
	return GameTexturesIterator->second;
}