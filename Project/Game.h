#ifndef GAME_H
#define GAME_H


#include "MainMenuState.h"

class Game {
public:
	//Constructor/Destructors
	Game();
	virtual ~Game();
	//Functions

	//Regular
	void endApplication();
	
	//Update
	void processEvents();
	void update();

	void updateDt();
	//Render
	void render();
	//Core
	void run();

private:
	//Variables
	sf::RenderWindow* mWindow;
	sf::Event sfEvent;
	std::vector<sf::VideoMode> videomodes;
	sf::ContextSettings windowSettings;
	bool fullscreen;
	sf::Clock dtClock;
	//Map mMap;
	//Character mPlayer;
	float dt;

	std::stack<State*> states;
	std::map<std::string, int> supportedKeys;

	

	//Initialization
	void initVariables();
	void initWindow();
	void initKeys();
	void initStates();

	


	

};
#endif
