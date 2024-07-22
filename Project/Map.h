#ifndef MAP_H
#define MAP_H

#include <SFML/Graphics.hpp>

class Map {
public:
	Map();
	~Map();

	void update(sf::Time deltaTime);
	void render(sf::RenderWindow& window);


private:
	sf::Sprite mSprite;
	sf::Texture mTexture;
};

#endif
