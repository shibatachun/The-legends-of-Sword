#ifndef TILEMAP_H
#define TILEMAP_H

#include "Tile.h"
#include "Gui.h"

class TileMap
{
private:
	void clear();
	float gridSizeF;
	unsigned gridSizeU;
	unsigned layers;
	sf::Vector2u maxSize;
	sf::Vector2i maxMapSize;
	std::vector < std::vector<std::vector<Tile*>>> maps;
	std::string textureFile;
	sf::Texture tileSheet;
protected:
	
public:

	TileMap(float gridSize, unsigned width, unsigned height,std::string texture_file);
	virtual ~TileMap();
	//Functions
	//Accessors
	const sf::Texture* getTileSheet();
	const sf::Vector2i getMaxMapSize();
	void update();
	void render(sf::RenderTarget& target);
	void addtile(const unsigned x, const unsigned y, const unsigned z, const sf::IntRect &texture_rect);
	void removeTile(const unsigned x, const unsigned y, const unsigned z);

	void saveToFile(const std::string file_name);
	void loadFromFile(const std::string file_name);
	
};
#endif
