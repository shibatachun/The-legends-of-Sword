#ifndef STATE_H
#define STATE_H

#include "Player.h"
#include "GraphicsSettings.h"
#include "Gui.h"
class Player;
class GraphicsSettings;
class State;
class StateData
{
public:
	 StateData() {};
	//Variables
	float gridSize;
	sf::RenderWindow* window;
	GraphicsSettings* gfxSettings ;
	std::map<std::string, int>* supportedKeys ;
	std::stack<State*>* states;
	std::map<int, std::string>* textureResourcePath;

};


class State
{
private:

protected:
	StateData* stateData;
	std::stack<State*>* states;
	sf::RenderWindow* window;
	std::map<std::string, int>* supportKeys;
	std::map<std::string, int> keybinds;
	

	bool quit;
	bool paused;
	float keytime;
	float keytimeMax;
	float gridSize;

	sf::Vector2i mousePosScreen;
	sf::Vector2i mousePosWindow;
	sf::Vector2f mousePosView;
	sf::Vector2i mousePosGrid;


	//Functions
	virtual void initKeybinds() = 0;

	

public:
	State(StateData* state_date);
	virtual ~State();

	
	//virtual void endStateUpdate() = 0;

	//Accessors
	const bool& getQuit() const;
	const bool getKeytime();
	
	//Functions
	

	void endState();
	void pauseState();
	void unpauseState();

	virtual void updateMousePositions(sf::View* view = NULL);
	virtual void updateInput(const float& dt) = 0;
	virtual void updateKeytime(const float& dt);
	virtual void update(const float& dt) = 0;
	virtual void render(sf::RenderTarget* target = NULL) = 0;

};

#endif


