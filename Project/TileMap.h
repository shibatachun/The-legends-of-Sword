#ifndef TILEMAP_H
#define TILEMAP_H

#include "Tile.h"
#include "Gui.h"

class TileMap
{
private:
	float gridSizeF;
	unsigned gridSizeU;
	unsigned layers;
	sf::Vector2u maxSize;
	std::vector < std::vector<std::vector<Tile*>>> maps;
	sf::Texture tileTextureSheet;
protected:
	
public:

	TileMap(float gridSize, unsigned width, unsigned height);
	virtual ~TileMap();
	//Functions

	void update();
	void render(sf::RenderTarget& target);
	void addtile(const unsigned x, const unsigned y, const unsigned z, const sf::IntRect &texture_rect);
	void removeTile(const unsigned x, const unsigned y, const unsigned z);
	
};
#endif
