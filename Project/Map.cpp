#include "Map.h"
#include <iostream> 
Map::Map() {
	if (!mTexture.loadFromFile("..\\MasterSimple.png"))
	{
		std::cerr << "Failed to load map texture" << std::endl;
	}
	mSprite.setTexture(mTexture);

}
Map::~Map() {}

void Map::update(sf::Time deltatTIme) {

}

void Map::render(sf::RenderWindow& window) {
	window.draw(mSprite);
}
