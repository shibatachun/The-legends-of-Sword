#ifndef PAUSEMENU_H
#define PAUSEMENU_H
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
#include "Button.h"
class PauseMenu
{
private:
	sf::Font* font;
	sf::Text menuText;

	sf::RectangleShape background;
	sf::RectangleShape container;

	std::map<std::string, Button*> buttons;
public:
	PauseMenu(sf::RenderWindow& window, sf::Font& font);
	virtual ~PauseMenu();

	//Functions
	void update();
	void render(sf::RenderTarget& target);
};

#endif

