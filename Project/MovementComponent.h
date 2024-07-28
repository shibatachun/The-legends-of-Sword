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

enum movement_states {IDLE=0,MOVING, MOVEING_LEFT, MOVING_RIGHT,MOVING_UP,MOVING_DOWN};
class MovementComponent
{
private:
	sf::Sprite& sprite;

	float maxVelocity;
	float acceleration;
	float deceleration;

	sf::Vector2f velocity;
	std::map<std::string, bool> movestate;
	 
	//Initializer functions

public:

	MovementComponent(sf::Sprite& sprite,
		float maxVelocity, float acceleration, float deceleration);
	virtual ~MovementComponent();


	//Accessors
	const float& getMaxVelocity() const;
	const sf::Vector2f& getVelocity() const;



	//Functions
	const bool getState(const short unsigned state) const;


	void move(const float dir_x, const float dir_y, const float& dt);
	void update(const float& dt);
};

#endif
