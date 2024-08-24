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
	virtual const sf::Vector2f& getPosition() const;
	virtual const bool& getCollision() const;
	virtual const sf::FloatRect getGlobalBounds() const;
	virtual const bool intersects(const sf::FloatRect bounds) const;
	virtual const std::string getAsString() const = 0;
	
	virtual void update() = 0;
	virtual void render(sf::RenderTarget& target, sf::Shader* shader = NULL, const sf::Vector2f player_position = sf::Vector2f()) = 0;

};

#endif




