///////////////////////////////////////////////////////////
///// Towers! game - Processing  and Storing Textures
///////////////////////////////////////////////////////////
#pragma once

// headers
#include <SFML/Graphics.hpp>
#include <map>

// class for textures, it can load texture and store it for later
class Textures {
public:
	//  add new texture, it takes 2 argument,name of texture and path to texture for loading it
	void AddNewTexture(std::string NameOfTexture, std::string PathToTextureData);
	// takes one argument name of texture and return that texture, if texture does not exist  it throw exception
	sf::Texture& GetTexture(std::string NameOftexture);
private:
	std::map<std::string, sf::Texture> GameTextures; 
	std::map<std::string, sf::Texture>::iterator GameTexturesIterator; 	
};