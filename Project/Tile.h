#ifndef TILE_H
#define TILE_H


enum TileTypes {DEFAULT = 0,DAMAGING,DOODAD,ENEMYSPAWN};
class Tile
{
private:

protected:
	sf::Sprite shape;
	bool collision;
	short type;
	int tileSheetIndex;

public:
	Tile();
	Tile(int grid_x, int grid_y, float gridSizeF,int tileSheetIndex, const sf::Texture& texture,const sf::IntRect rect, bool collision = false, short type = TileTypes::DEFAULT);
	virtual ~Tile();
	//Accessors
	const short& getType() const;
	const int& getTileIndex() const;
	//Functions
	const sf::Vector2f& getPosition() const;
	const bool& getCollision() const;
	const sf::FloatRect getGlobalBounds() const;
	const bool intersects(const sf::FloatRect bounds) const;
	const std::string getAsString() const;
	
	virtual void update();
	virtual void render(sf::RenderTarget& target, sf::Shader* shader = NULL, const sf::Vector2f player_position = sf::Vector2f());

};

#endif




