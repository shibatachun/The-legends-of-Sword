#ifndef ENTITY_H

#include<vector>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>

#include <iostream>
#include <fstream>
#include <sstream>
#include <stack>
#include <ctime>
#include <cstdlib>
#include <map>
#include <vector>
class Entity
{
private:
	void initVariables();

	//Can directly access by child classes
protected:
	sf::Texture* texture;
	sf::Sprite* sprite;


	float movementSpeed;
	

public:
	Entity();
	virtual ~Entity();
	//Component functions
	void createSprite(sf::Texture* texture);
	//Functions

	virtual void move(const float dt, const float x, const float y);
	virtual void update(const float& dt) ;
	virtual void render(sf::RenderTarget* target);


};
#endif // 



