#ifndef REGULARTILE_H
#define REGULARTILE_H
#include "Tile.h"
class RegularTile :
    public Tile
{
private:

protected:

public:
	RegularTile(int grid_x, int grid_y, float gridSizeF, int tileSheetIndex, const sf::Texture& texture, const sf::IntRect rect, bool collision = false, short type = TileTypes::DEFAULT);
	virtual~RegularTile();

	//Accessors

	const short& getType() const;
	const int& getTileIndex() const;
	//Functions

	virtual const bool& getCollision() const;

	virtual const std::string getAsString() const;

	virtual void update();
	virtual void render(sf::RenderTarget& target, sf::Shader* shader = NULL, const sf::Vector2f player_position = sf::Vector2f());
};






#endif




