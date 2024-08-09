#ifndef TILE_H
#define TILE_H


enum TileTypes {DEFAULT = 0,DAMAGING};
class Tile
{
private:

protected:
	sf::RectangleShape shape;
	bool collision;
	short type;

public:
	Tile();
	Tile(unsigned grid_x, unsigned grid_y, float gridSizeF, const sf::Texture& texture,const sf::IntRect rect, bool collision = false, short type = TileTypes::DEFAULT);
	virtual ~Tile();


	//Functions
	const sf::Vector2f& getPosition() const;
	const bool& getCollision() const;
	const sf::FloatRect getGlobalBounds() const;
	const bool intersects(const sf::FloatRect bounds) const;
	const std::string getAsString() const;
	
	void update();
	void render(sf::RenderTarget& target);

};

#endif




