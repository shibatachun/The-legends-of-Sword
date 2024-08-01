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
	std::vector < std::vector<std::vector<Tile>>> maps;
protected:
	
public:

	TileMap();
	virtual ~TileMap();
	//Functions

	void update();
	void render(sf::RenderTarget& target);
	
};
#endif
