#ifndef STATE_H
#define STATE_H

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


#include "Map.h"
#include "Character.h"
class State
{

private:
	sf::RenderWindow* window;
	std::vector<sf::Texture> textures;
	bool quit;

public:
	State(sf::RenderWindow* window);
	virtual ~State();

	const bool& getQuit() const;

	virtual void updateKeybinds(const float& dt) = 0;
	virtual void update(const float& dt ) = 0;
	virtual void render(sf::RenderTarget* target = nullptr) = 0;
	virtual void checkForQuit();
	virtual void endState() = 0;


};

#endif


