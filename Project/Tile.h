#ifndef TILE_H
#define TILE_H

class Tile
{
private:

protected:
	sf::RectangleShape shape;
public:
	Tile();
	Tile(float x, float y, float gridSizeF, const sf::Texture& texture,const sf::IntRect rect);
	virtual ~Tile();


	//Functions
	void render(sf::RenderTarget &target);
	void update();

};

#endif




