#ifndef TILEMAP_H
#define TILEMAP_H

#include "Tile.h"
#include "Gui.h"
#include "Entity.h"

class Tile;
class Entity;
class TileMap
{
private:
	void clear();
	float gridSizeF;
	int gridSizeI;
	int layers;
	int tileSheetCount;
	short tileIndex;
	sf::Vector2i maxSize;    //maxSize
	
	sf::Vector2f maxSizeWorldF;
	std::vector < std::vector< std::vector<std::vector<Tile*> > > >  maps;
	std::stack<Tile*> deferredRenderStack;
	std::string textureFile;
	std::map<int, std::string> textureFileSet;
	std::map<int, sf::Texture> tileSheetSet;
	sf::Texture tileSheet;
	sf::RectangleShape collisionBox;

	//Culling
	int fromX;
	int toX;
	int fromY;
	int toY;
	int layer;
protected:
	
public:

	TileMap(float gridSize, int width, int height, std::map<int, std::string>& textureFileSet);
	virtual ~TileMap();

	

	//Initilizier
	void initTextureSet();
	//Accessors
	const sf::Texture* getTileSheet();
	const sf::Vector2f getMaxMapSize();
	const int getLayerSize(const int x, const int y, const int z) const;

	//Functions
	void addtile(const int x, const int y, const int z,  int tileIndex , const sf::IntRect &texture_rect, const bool& collision, const short& type);
	void removeTile(const int x, const int y, const int z);

	void saveToFile(const std::string file_name);
	void loadFromFile(const std::string file_name);


	void updateCollision(Entity* entity, const float& dt);
	void update();
	void render(sf::RenderTarget& target, const sf::Vector2i& gridPosition);
	void renderDeferred(sf::RenderTarget& target);
};
#endif
