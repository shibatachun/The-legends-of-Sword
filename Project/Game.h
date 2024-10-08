#ifndef GAME_H
#define GAME_H


#include "MainMenuState.h"
#include "State.h"

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
	GraphicsSettings gfxSettings;
	StateData stateData;
	sf::RenderWindow* mWindow;
	
	sf::Event sfEvent;
	
	sf::Clock dtClock;
	//Map mMap;
	//Character mPlayer;
	float dt;
	float gridSize;
	std::stack<State*> states;
	std::map<std::string, int> supportedKeys;
	std::map<int, std::string> textureResource;

	

	//Initialization
	void initVariables();
	void initWindow();
	void initKeys();
	void initGraphicsSettings();
	void initStateData();
	void initStates();
	void initTextureResource();

	

	

};
#endif
