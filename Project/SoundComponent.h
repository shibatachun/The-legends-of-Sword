#ifndef SOUNDCOMPONENT_H
#define SOUNDCOMPONENT_H


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

class SoundComponent
{
private:
	


public:
	SoundComponent(float dt,sf::Music);
	virtual ~SoundComponent();

	//Function
	void update();
	void play();
	void pause();

	
};

#endif

