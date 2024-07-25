#ifndef MOVEMENTCOMPONENT_H
#define MOVEMENTCOMPONENT_H

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
class MovementComponent
{
private:
	sf::Sprite& sprite;

	float maxVelocity;
	float acceleration;
	float deceleration;

	sf::Vector2f velocity;


	//Initializer functions

public:

	MovementComponent(sf::Sprite& sprite,
		float maxVelocity, float acceleration, float deceleration);
	virtual ~MovementComponent();


	//Accessors
	const sf::Vector2f& getVelocity() const;

	//Functions
	void move(const float dir_x, const float dir_y, const float& dt);
	void update(const float& dt);
};

#endif
