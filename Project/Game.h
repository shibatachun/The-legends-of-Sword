#ifndef GAME_H
#define GAME_H

#include "GameState.h"

class Game {
public:
	//Constructor/Destructors
	Game();
	virtual ~Game();
	//Functions

	void run();
	void processEvents();
	void update();
	void render();
	void updateDt();

private:
	//Variables
	sf::RenderWindow* mWindow;
	sf::Event sfEvent;
	sf::Clock dtClock;
	//Map mMap;
	//Character mPlayer;
	float dt;

	std::stack<State*> states;

	

	//Initialization
	void initWindow();
	void initStates();

	


	

};
#endif
