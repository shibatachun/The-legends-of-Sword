#ifndef STATE_H
#define STATE_H

#include "Player.h"

#include "Button.h"

#include "Map.h"
#include "Character.h"
class State
{
private:

protected:
	std::stack<State*>* states;
	sf::RenderWindow* window;
	std::map<std::string, int>* supportKeys;
	std::map<std::string, int> keybinds;
	sf::Font font;
	bool quit;
	bool paused;

	sf::Vector2i mousePosScreen;
	sf::Vector2i mousePosWindow;
	sf::Vector2f mousePosView;
	//Resources
	std::map<std::string,sf::Texture> textures;

	//Functions
	virtual void initKeybinds() = 0;

	

public:
	State(sf::RenderWindow* window,std::map<std::string,int>* supportedKeys, std::stack<State*>* states);
	virtual ~State();

	const bool& getQuit() const;
	
	//virtual void endStateUpdate() = 0;

	virtual void updateInput(const float& dt) = 0;
	virtual void update(const float& dt ) = 0;
	virtual void render(sf::RenderTarget* target = NULL) = 0;
	
	void endState();
	void pauseState();
	void unpauseState();
	virtual void updateMousePositions();


};

#endif


