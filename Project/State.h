#ifndef STATE_H
#define STATE_H

#include "Player.h"

#include "Gui.h"

class State
{
private:

protected:
	std::stack<State*>* states;
	sf::RenderWindow* window;
	std::map<std::string, int>* supportKeys;
	std::map<std::string, int> keybinds;
	

	bool quit;
	bool paused;
	float keytime;
	float keytimeMax;

	sf::Vector2i mousePosScreen;
	sf::Vector2i mousePosWindow;
	sf::Vector2f mousePosView;


	//Functions
	virtual void initKeybinds() = 0;

	

public:
	State(sf::RenderWindow* window,std::map<std::string,int>* supportedKeys, std::stack<State*>* states);
	virtual ~State();

	
	//virtual void endStateUpdate() = 0;

	//Accessors
	const bool& getQuit() const;
	const bool getKeytime();
	
	//Functions
	void endState();
	void pauseState();
	void unpauseState();

	virtual void updateMousePositions();
	virtual void updateInput(const float& dt) = 0;
	virtual void updateKeytime(const float& dt);
	virtual void update(const float& dt) = 0;
	virtual void render(sf::RenderTarget* target = NULL) = 0;

};

#endif


